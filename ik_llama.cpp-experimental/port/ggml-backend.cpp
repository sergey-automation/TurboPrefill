// Based on ik_llama.cpp, commit 6198a356, by Ivan Kawrakow (ikawrakow).
//
// Experimental port of TurboPrefill by Trykhlieb to ik_llama.cpp.
// Version: v6.1

#include "ggml-backend-impl.h"
#include "ggml-alloc.h"
#include "ggml-impl.h"
#include "ggml-rpc.h"
#include "ggml-moe-prefetch.h"

#include <cassert>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
#include <chrono>
#include <barrier>
#include <thread>
#ifdef GGML_USE_OPENMP
#include <omp.h>
#endif

#define IK_PRINT_TIMING 0

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// backend buffer type

const char * ggml_backend_buft_name(ggml_backend_buffer_type_t buft) {
    return buft->iface.get_name(buft);
}

GGML_CALL ggml_backend_buffer_t ggml_backend_buft_alloc_buffer(ggml_backend_buffer_type_t buft, size_t size) {
    return buft->iface.alloc_buffer(buft, size);
}

size_t ggml_backend_buft_get_alignment(ggml_backend_buffer_type_t buft) {
    return buft->iface.get_alignment(buft);
}

size_t ggml_backend_buft_get_max_size(ggml_backend_buffer_type_t buft) {
    // get_max_size is optional, defaults to SIZE_MAX
    if (buft->iface.get_max_size) {
        return buft->iface.get_max_size(buft);
    }
    return SIZE_MAX;
}

GGML_CALL size_t ggml_backend_buft_get_alloc_size(ggml_backend_buffer_type_t buft, const struct ggml_tensor * tensor) {
    // get_alloc_size is optional, defaults to ggml_nbytes
    if (buft->iface.get_alloc_size) {
        size_t size = buft->iface.get_alloc_size(buft, tensor);
        //assert(size >= ggml_nbytes(tensor));
        return size;
    }
    return ggml_nbytes(tensor);
}

bool ggml_backend_buft_is_host(ggml_backend_buffer_type_t buft) {
    if (buft->iface.is_host) {
        return buft->iface.is_host(buft);
    }
    return false;
}

// backend buffer

GGML_CALL ggml_backend_buffer_t ggml_backend_buffer_init(
               ggml_backend_buffer_type_t      buft,
        struct ggml_backend_buffer_i           iface,
               ggml_backend_buffer_context_t   context,
               size_t                          size) {
    ggml_backend_buffer_t buffer = new ggml_backend_buffer {
        /* .interface = */ iface,
        /* .buft      = */ buft,
        /* .context   = */ context,
        /* .size      = */ size,
        /* .usage     = */ GGML_BACKEND_BUFFER_USAGE_ANY
    };

    return buffer;
}

const char * ggml_backend_buffer_name(ggml_backend_buffer_t buffer) {
    return buffer->iface.get_name(buffer);
}

void ggml_backend_buffer_free(ggml_backend_buffer_t buffer) {
    if (buffer == NULL) {
        return;
    }

    if (buffer->iface.free_buffer != NULL) {
        buffer->iface.free_buffer(buffer);
    }
    delete buffer;
    //free(buffer);
}

size_t ggml_backend_buffer_get_size(ggml_backend_buffer_t buffer) {
    return buffer->size;
}

void * ggml_backend_buffer_get_base(ggml_backend_buffer_t buffer) {
    void * base = buffer->iface.get_base(buffer);

    GGML_ASSERT(base != NULL && "backend buffer base cannot be NULL");

    return base;
}

GGML_CALL void ggml_backend_buffer_init_tensor(ggml_backend_buffer_t buffer, struct ggml_tensor * tensor) {
    // init_tensor is optional
    if (buffer->iface.init_tensor) {
        buffer->iface.init_tensor(buffer, tensor);
    }
}

size_t ggml_backend_buffer_get_alignment (ggml_backend_buffer_t buffer) {
    return ggml_backend_buft_get_alignment(ggml_backend_buffer_get_type(buffer));
}

size_t ggml_backend_buffer_get_max_size(ggml_backend_buffer_t buffer) {
    return ggml_backend_buft_get_max_size(ggml_backend_buffer_get_type(buffer));
}

size_t ggml_backend_buffer_get_alloc_size(ggml_backend_buffer_t buffer, const struct ggml_tensor * tensor) {
    return ggml_backend_buft_get_alloc_size(ggml_backend_buffer_get_type(buffer), tensor);
}

void ggml_backend_buffer_clear(ggml_backend_buffer_t buffer, uint8_t value) {
    buffer->iface.clear(buffer, value);
}

bool ggml_backend_buffer_is_host(ggml_backend_buffer_t buffer) {
    return buffer && ggml_backend_buft_is_host(ggml_backend_buffer_get_type(buffer));
}

void ggml_backend_buffer_set_usage(ggml_backend_buffer_t buffer, enum ggml_backend_buffer_usage usage) {
    buffer->usage = usage;

    // FIXME: add a generic callback to the buffer interface
    if (ggml_backend_buffer_is_multi_buffer(buffer)) {
        ggml_backend_multi_buffer_set_usage(buffer, usage);
    }
}

enum ggml_backend_buffer_usage ggml_backend_buffer_get_usage(ggml_backend_buffer_t buffer) {
    return buffer->usage;
}

ggml_backend_buffer_type_t ggml_backend_buffer_get_type(ggml_backend_buffer_t buffer) {
    return buffer->buft;
}

void ggml_backend_buffer_reset(ggml_backend_buffer_t buffer) {
    if (buffer->iface.reset) {
        buffer->iface.reset(buffer);
    }
}

bool ggml_backend_buffer_copy_tensor(const struct ggml_tensor * src, struct ggml_tensor * dst) {
    ggml_backend_buffer_t dst_buf = dst->view_src ? dst->view_src->buffer : dst->buffer;
    if (dst_buf->iface.cpy_tensor) {
        return dst_buf->iface.cpy_tensor(dst_buf, src, dst);
    }
    return false;
}

// backend

ggml_guid_t ggml_backend_guid(ggml_backend_t backend) {
    if (backend == NULL) {
        return NULL;
    }
    return backend->guid;
}

const char * ggml_backend_name(ggml_backend_t backend) {
    if (backend == NULL) {
        return "NULL";
    }
    return backend->iface.get_name(backend);
}

void ggml_backend_free(ggml_backend_t backend) {
    if (backend == NULL) {
        return;
    }

    backend->iface.free(backend);
}

ggml_backend_buffer_type_t ggml_backend_get_default_buffer_type(ggml_backend_t backend) {
    return backend->iface.get_default_buffer_type(backend);
}

ggml_backend_buffer_t ggml_backend_alloc_buffer(ggml_backend_t backend, size_t size) {
    return ggml_backend_buft_alloc_buffer(ggml_backend_get_default_buffer_type(backend), size);
}

size_t ggml_backend_get_alignment(ggml_backend_t backend) {
    return ggml_backend_buft_get_alignment(ggml_backend_get_default_buffer_type(backend));
}

size_t ggml_backend_get_max_size(ggml_backend_t backend) {
    return ggml_backend_buft_get_max_size(ggml_backend_get_default_buffer_type(backend));
}

void ggml_backend_tensor_set_async(ggml_backend_t backend, struct ggml_tensor * tensor, const void * data, size_t offset, size_t size) {
    GGML_ASSERT(tensor->data != NULL && "tensor not allocated");
    if (offset + size > ggml_nbytes(tensor)) fprintf(stderr, "%s(%s): offset = %zu, size = %zu, nbytes = %zu\n", __func__, tensor->name, offset, size, ggml_nbytes(tensor));
    GGML_ASSERT(offset + size <= ggml_nbytes(tensor) && "tensor write out of bounds");

    if (backend->iface.set_tensor_async == NULL) {
        ggml_backend_tensor_set(tensor, data, offset, size);
    } else {
        backend->iface.set_tensor_async(backend, tensor, data, offset, size);
    }
}

void ggml_backend_tensor_get_async(ggml_backend_t backend, const struct ggml_tensor * tensor, void * data, size_t offset, size_t size) {
    GGML_ASSERT(tensor->data != NULL && "tensor not allocated");
    GGML_ASSERT(offset + size <= ggml_nbytes(tensor) && "tensor read out of bounds");

    if (backend->iface.get_tensor_async == NULL) {
        ggml_backend_tensor_get(tensor, data, offset, size);
    } else {
        backend->iface.get_tensor_async(backend, tensor, data, offset, size);
    }
}

GGML_CALL void ggml_backend_tensor_set(struct ggml_tensor * tensor, const void * data, size_t offset, size_t size) {
    ggml_backend_buffer_t buf = tensor->view_src ? tensor->view_src->buffer : tensor->buffer;

    GGML_ASSERT(buf != NULL && "tensor buffer not set");
    GGML_ASSERT(tensor->data != NULL && "tensor not allocated");
    GGML_ASSERT(offset + size <= ggml_nbytes(tensor) && "tensor write out of bounds");

    if (!size) {
        return;
    }


#if IK_PRINT_TIMING
    int64_t tim1 = ggml_time_us();
#endif
    buf->iface.set_tensor(buf, tensor, data, offset, size);
#if IK_PRINT_TIMING
    int64_t tim2 = ggml_time_us();
    //printf("%s(%s) %zu %d us\n", __func__, tensor->name, size, (int)(tim2-tim1));
    printf("%s(%s): %d us\n", __func__, tensor->name, (int)(tim2-tim1));
#endif

}

GGML_CALL void ggml_backend_tensor_get(const struct ggml_tensor * tensor, void * data, size_t offset, size_t size) {
    ggml_backend_buffer_t buf = tensor->view_src ? tensor->view_src->buffer : tensor->buffer;

    GGML_ASSERT(buf != NULL && "tensor buffer not set");
    GGML_ASSERT(tensor->data != NULL && "tensor not allocated");
    GGML_ASSERT(offset + size <= ggml_nbytes(tensor) && "tensor read out of bounds");

    if (!size) {
        return;
    }

#if IK_PRINT_TIMING
    int64_t tim1 = ggml_time_us();
#endif
    buf->iface.get_tensor(buf, tensor, data, offset, size);
#if IK_PRINT_TIMING
    int64_t tim2 = ggml_time_us();
    //printf("%s(%s) %zu %d us\n", __func__, tensor->name, size, (int)(tim2-tim1));
    printf("%s(%s): %d us\n", __func__, tensor->name, (int)(tim2-tim1));
#endif
}

static void ggml_backend_tensor_memset(struct ggml_tensor* tensor, uint8_t value, size_t offset, size_t size) {
    ggml_backend_buffer_t buf = tensor->view_src ? tensor->view_src->buffer : tensor->buffer;

    if (size == 0) {
        return;
    }

    GGML_ASSERT(buf != NULL && "tensor buffer not set");
    GGML_ASSERT(tensor->data != NULL && "tensor not allocated");
    GGML_ASSERT(offset + size <= ggml_nbytes(tensor) && "tensor write out of bounds");
    GGML_ASSERT(buf->iface.memset_tensor != NULL && "memset not implemented by backend buffer");

    buf->iface.memset_tensor(buf, tensor, value, offset, size);
}

void ggml_backend_synchronize(ggml_backend_t backend) {
    if (backend->iface.synchronize == NULL) {
        return;
    }

    backend->iface.synchronize(backend);
}

ggml_backend_graph_plan_t ggml_backend_graph_plan_create(ggml_backend_t backend, struct ggml_cgraph * cgraph) {
    GGML_ASSERT(backend->iface.graph_plan_create != NULL);

    return backend->iface.graph_plan_create(backend, cgraph);
}

void ggml_backend_graph_plan_free(ggml_backend_t backend, ggml_backend_graph_plan_t plan) {
    GGML_ASSERT(backend->iface.graph_plan_free != NULL);

    backend->iface.graph_plan_free(backend, plan);
}

enum ggml_status ggml_backend_graph_plan_compute(ggml_backend_t backend, ggml_backend_graph_plan_t plan) {
    GGML_ASSERT(backend->iface.graph_plan_compute != NULL);

    return backend->iface.graph_plan_compute(backend, plan);
}

enum ggml_status ggml_backend_graph_compute(ggml_backend_t backend, struct ggml_cgraph * cgraph) {
    enum ggml_status err = ggml_backend_graph_compute_async(backend, cgraph);
    ggml_backend_synchronize(backend);
    return err;
}

enum ggml_status ggml_backend_graph_compute_async(ggml_backend_t backend, struct ggml_cgraph * cgraph) {
    return backend->iface.graph_compute(backend, cgraph);
}

bool ggml_backend_supports_op(ggml_backend_t backend, const struct ggml_tensor * op) {
    return backend->iface.supports_op(backend, op);
}

bool ggml_backend_supports_buft(ggml_backend_t backend, ggml_backend_buffer_type_t buft) {
    return backend->iface.supports_buft(backend, buft);
}

bool ggml_backend_offload_op(ggml_backend_t backend, const struct ggml_tensor * op) {
    if (backend->iface.offload_op != NULL) {
        return backend->iface.offload_op(backend, op);
    }
    return false;
}

// backend copy

static bool ggml_are_same_layout(const struct ggml_tensor * a, const struct ggml_tensor * b) {
    if (a->type != b->type) {
        return false;
    }
    for (int i = 0; i < GGML_MAX_DIMS; i++) {
        if (a->ne[i] != b->ne[i]) {
            return false;
        }
        if (a->nb[i] != b->nb[i]) {
            return false;
        }
    }
    return true;
}

void ggml_backend_tensor_copy(struct ggml_tensor * src, struct ggml_tensor * dst) {
    GGML_ASSERT(ggml_are_same_layout(src, dst) && "cannot copy tensors with different layouts");

    if (src == dst) {
        return;
    }

    if (ggml_backend_buffer_is_host(src->buffer)) {
        ggml_backend_tensor_set(dst, src->data, 0, ggml_nbytes(src));
    } else if (ggml_backend_buffer_is_host(dst->buffer)) {
        ggml_backend_tensor_get(src, dst->data, 0, ggml_nbytes(src));
    } else if (!ggml_backend_buffer_copy_tensor(src, dst)) {
#ifndef NDEBUG
        fprintf(stderr, "%s: warning: slow copy from %s to %s\n", __func__, ggml_backend_buffer_name(src->buffer), ggml_backend_buffer_name(dst->buffer));
#endif
        size_t nbytes = ggml_nbytes(src);
        void * data = malloc(nbytes);
        ggml_backend_tensor_get(src, data, 0, nbytes);
        ggml_backend_tensor_set(dst, data, 0, nbytes);
        free(data);
    }
}

void ggml_backend_tensor_copy_async(ggml_backend_t backend_src, ggml_backend_t backend_dst, struct ggml_tensor * src, struct ggml_tensor * dst) {
    GGML_ASSERT(ggml_are_same_layout(src, dst) && "cannot copy tensors with different layouts");

    if (src == dst) {
        return;
    }

    if (backend_dst->iface.cpy_tensor_async != NULL) {
        if (backend_dst->iface.cpy_tensor_async(backend_src, backend_dst, src, dst)) {
            return;
        }
    }

    // an async copy would normally happen after all the queued operations on both backends are completed
    // to simulate the same behavior, we need to synchronize both backends first, and do a blocking copy
    ggml_backend_synchronize(backend_src);
    ggml_backend_synchronize(backend_dst);
    ggml_backend_tensor_copy(src, dst);
}

// events

ggml_backend_event_t ggml_backend_event_new(ggml_backend_t backend) {
    if (backend->iface.event_new == NULL) {
        return NULL;
    }
    return backend->iface.event_new(backend);
}

void ggml_backend_event_free(ggml_backend_event_t event) {
    if (event == NULL) {
        return;
    }
    event->backend->iface.event_free(event);
}

void ggml_backend_event_record(ggml_backend_event_t event) {
    GGML_ASSERT(event->backend->iface.event_record != NULL);

    event->backend->iface.event_record(event);
}

void ggml_backend_event_synchronize(ggml_backend_event_t event) {
    GGML_ASSERT(event->backend->iface.event_synchronize != NULL);

    event->backend->iface.event_synchronize(event);
}

void ggml_backend_event_wait(ggml_backend_t backend, ggml_backend_event_t event) {
    GGML_ASSERT(backend->iface.event_wait != NULL);

    backend->iface.event_wait(backend, event);
}

// backend registry

#define GGML_REG_MAX_BACKENDS 64

struct ggml_backend_reg {
    char name[128];
    ggml_backend_init_fn init_fn;
    ggml_backend_buffer_type_t default_buffer_type;
    void * user_data;
};

static struct ggml_backend_reg ggml_backend_registry[GGML_REG_MAX_BACKENDS];
static size_t ggml_backend_registry_count = 0;

GGML_CALL static ggml_backend_t ggml_backend_reg_cpu_init(const char * params, void * user_data);

#ifdef GGML_USE_CUDA
extern "C" GGML_CALL void ggml_backend_cuda_reg_devices(void);
#endif
#ifdef GGML_USE_SYCL
extern "C" void ggml_backend_sycl_reg_devices(void);
#endif
#ifdef GGML_USE_METAL
extern "C" GGML_CALL ggml_backend_t ggml_backend_reg_metal_init(const char * params, void * user_data);
extern "C" GGML_CALL ggml_backend_buffer_type_t ggml_backend_metal_buffer_type(void);
#endif
#ifdef GGML_USE_VULKAN
extern "C" GGML_CALL int ggml_backend_vk_reg_devices(void);
#endif
#ifdef GGML_USE_CANN
extern "C" GGML_CALL int ggml_backend_cann_reg_devices(void);
#endif
#ifdef GGML_USE_RPC
extern "C" GGML_CALL void ggml_backend_rpc_reg_devices(void);
#endif

GGML_CALL static void ggml_backend_registry_init(void) {
    static bool initialized = false;

    if (initialized) {
        return;
    }

    initialized = true;

    ggml_backend_register("CPU", ggml_backend_reg_cpu_init, ggml_backend_cpu_buffer_type(), NULL);

    // add forward decls here to avoid including the backend headers
#ifdef GGML_USE_CUDA
    ggml_backend_cuda_reg_devices();
#endif

#ifdef GGML_USE_SYCL
    ggml_backend_sycl_reg_devices();
#endif

#ifdef GGML_USE_METAL
    ggml_backend_register("Metal", ggml_backend_reg_metal_init, ggml_backend_metal_buffer_type(), NULL);
#endif

#ifdef GGML_USE_VULKAN
    ggml_backend_vk_reg_devices();
#endif

#ifdef GGML_USE_CANN
    ggml_backend_cann_reg_devices();
#endif
#ifdef GGML_USE_RPC
    ggml_backend_rpc_reg_devices();
#endif
}

GGML_CALL void ggml_backend_register(const char * name, ggml_backend_init_fn init_fn, ggml_backend_buffer_type_t default_buffer_type, void * user_data) {
    GGML_ASSERT(ggml_backend_registry_count < GGML_REG_MAX_BACKENDS);

    size_t id = ggml_backend_registry_count;

    ggml_backend_registry[id] = ggml_backend_reg {
        /* .name                = */ {0},
        /* .fn                  = */ init_fn,
        /* .default_buffer_type = */ default_buffer_type,
        /* .user_data           = */ user_data
    };

    snprintf(ggml_backend_registry[id].name, sizeof(ggml_backend_registry[id].name), "%s", name);

#ifndef NDEBUG
    fprintf(stderr, "%s: registered backend %s\n", __func__, name);
#endif

    ggml_backend_registry_count++;
}

// Backend (reg) enumeration
static bool striequals(const char* a, const char* b) {
    for (; *a && *b; a++, b++) {
        if (std::tolower(*a) != std::tolower(*b)) {
            return false;
        }
    }
    return *a == *b;
}

size_t ggml_backend_reg_get_count(void) {
    ggml_backend_registry_init();

    return ggml_backend_registry_count;
}

size_t ggml_backend_reg_find_by_name(const char * name) {
    ggml_backend_registry_init();

    for (size_t i = 0; i < ggml_backend_registry_count; i++) {
        // TODO: case insensitive in a portable way
        if (striequals(ggml_backend_registry[i].name, name)) {
            return i;
        }
    }

    // not found
    return SIZE_MAX;
}

// init from backend:params string
ggml_backend_t ggml_backend_reg_init_backend_from_str(const char * backend_str) {
    ggml_backend_registry_init();

    const char * params = strchr(backend_str, ':');
    char backend_name[128];
    if (params == NULL) {
        snprintf(backend_name, sizeof(backend_name), "%s", backend_str);
        params = "";
    } else {
        snprintf(backend_name, sizeof(backend_name), "%.*s", (int)(params - backend_str), backend_str);
        params++;
    }

    size_t backend_i = ggml_backend_reg_find_by_name(backend_name);

    if (backend_i == SIZE_MAX) {
        fprintf(stderr, "%s: backend %s not found\n", __func__, backend_name);
        return NULL;
    }

    return ggml_backend_reg_init_backend(backend_i, params);
}

const char * ggml_backend_reg_get_name(size_t i) {
    ggml_backend_registry_init();

    GGML_ASSERT(i < ggml_backend_registry_count);
    return ggml_backend_registry[i].name;
}

ggml_backend_t ggml_backend_reg_init_backend(size_t i, const char * params) {
    ggml_backend_registry_init();

    GGML_ASSERT(i < ggml_backend_registry_count);
    return ggml_backend_registry[i].init_fn(params, ggml_backend_registry[i].user_data);
}

ggml_backend_buffer_type_t ggml_backend_reg_get_default_buffer_type(size_t i) {
    ggml_backend_registry_init();

    GGML_ASSERT(i < ggml_backend_registry_count);
    return ggml_backend_registry[i].default_buffer_type;
}

ggml_backend_buffer_t ggml_backend_reg_alloc_buffer(size_t i, size_t size) {
    ggml_backend_registry_init();

    GGML_ASSERT(i < ggml_backend_registry_count);
    return ggml_backend_buft_alloc_buffer(ggml_backend_registry[i].default_buffer_type, size);
}

// backend CPU

static const size_t TENSOR_ALIGNMENT = 32; // required for mmap as gguf only guarantees 32-byte alignment

GGML_CALL static const char * ggml_backend_cpu_buffer_name(ggml_backend_buffer_t buffer) {
    return "CPU";

    GGML_UNUSED(buffer);
}

GGML_CALL static void * ggml_backend_cpu_buffer_get_base(ggml_backend_buffer_t buffer) {
    uintptr_t data = (uintptr_t)buffer->context;

    // align the buffer
    if (data % TENSOR_ALIGNMENT != 0) {
        data = GGML_PAD(data, TENSOR_ALIGNMENT);
    }

    return (void *)data;
}

GGML_CALL static void ggml_backend_cpu_buffer_free_buffer(ggml_backend_buffer_t buffer) {
    free(buffer->context);
}

static void ggml_backend_cpu_buffer_memset_tensor(ggml_backend_buffer_t buffer, struct ggml_tensor* tensor, uint8_t value, size_t offset, size_t size) {
    memset((char*)tensor->data + offset, value, size);

    GGML_UNUSED(buffer);
}

GGML_CALL static void ggml_backend_cpu_buffer_set_tensor(ggml_backend_buffer_t buffer, struct ggml_tensor * tensor, const void * data, size_t offset, size_t size) {
    memcpy((char *)tensor->data + offset, data, size);

    GGML_UNUSED(buffer);
}

GGML_CALL static void ggml_backend_cpu_buffer_get_tensor(ggml_backend_buffer_t buffer, const struct ggml_tensor * tensor, void * data, size_t offset, size_t size) {
    memcpy(data, (const char *)tensor->data + offset, size);

    GGML_UNUSED(buffer);
}

GGML_CALL static bool ggml_backend_cpu_buffer_cpy_tensor(ggml_backend_buffer_t buffer, const struct ggml_tensor * src, struct ggml_tensor * dst) {
    if (ggml_backend_buffer_is_host(src->buffer)) {
        memcpy(dst->data, src->data, ggml_nbytes(src));
        return true;
    }
    return false;

    GGML_UNUSED(buffer);
}

GGML_CALL static void ggml_backend_cpu_buffer_clear(ggml_backend_buffer_t buffer, uint8_t value) {
    memset(buffer->context, value, buffer->size);
}

static struct ggml_backend_buffer_i cpu_backend_buffer_i = {
    /* .get_name        = */ ggml_backend_cpu_buffer_name,
    /* .free_buffer     = */ ggml_backend_cpu_buffer_free_buffer,
    /* .get_base        = */ ggml_backend_cpu_buffer_get_base,
    /* .init_tensor     = */ NULL, // no initialization required
    /* .memset_tensor   = */ ggml_backend_cpu_buffer_memset_tensor,
    /* .set_tensor      = */ ggml_backend_cpu_buffer_set_tensor,
    /* .get_tensor      = */ ggml_backend_cpu_buffer_get_tensor,
    /* .cpy_tensor      = */ ggml_backend_cpu_buffer_cpy_tensor,
    /* .clear           = */ ggml_backend_cpu_buffer_clear,
    /* .reset           = */ NULL,
};

// for buffers from ptr, free is not called
static struct ggml_backend_buffer_i cpu_backend_buffer_i_from_ptr = {
    /* .get_name        = */ ggml_backend_cpu_buffer_name,
    /* .free_buffer     = */ NULL, // ptr is not owned by the buffer, so it does not need to be freed
    /* .get_base        = */ ggml_backend_cpu_buffer_get_base,
    /* .init_tensor     = */ NULL, // no initialization required
    /* .memset_tensor   = */ ggml_backend_cpu_buffer_memset_tensor,
    /* .set_tensor      = */ ggml_backend_cpu_buffer_set_tensor,
    /* .get_tensor      = */ ggml_backend_cpu_buffer_get_tensor,
    /* .cpy_tensor      = */ ggml_backend_cpu_buffer_cpy_tensor,
    /* .clear           = */ ggml_backend_cpu_buffer_clear,
    /* .reset           = */ NULL,
};

GGML_CALL static const char * ggml_backend_cpu_buffer_type_get_name(ggml_backend_buffer_type_t buft) {
    return "CPU";

    GGML_UNUSED(buft);
}

GGML_CALL static ggml_backend_buffer_t ggml_backend_cpu_buffer_type_alloc_buffer(ggml_backend_buffer_type_t buft, size_t size) {
    size += TENSOR_ALIGNMENT;   // malloc may return an address that is not aligned
    void * data = malloc(size); // TODO: use GGML_ALIGNED_MALLOC (move to ggml-impl.h)
    if (data == NULL) {
        fprintf(stderr, "%s: failed to allocate buffer of size %zu\n", __func__, size);
        return NULL;
    }

    return ggml_backend_buffer_init(buft, cpu_backend_buffer_i, data, size);
}

GGML_CALL static size_t ggml_backend_cpu_buffer_type_get_alignment(ggml_backend_buffer_type_t buft) {
    return TENSOR_ALIGNMENT;

    GGML_UNUSED(buft);
}

GGML_CALL static bool ggml_backend_cpu_buffer_type_is_host(ggml_backend_buffer_type_t buft) {
    return true;

    GGML_UNUSED(buft);
}

GGML_CALL ggml_backend_buffer_type_t ggml_backend_cpu_buffer_type(void) {
    static struct ggml_backend_buffer_type ggml_backend_cpu_buffer_type = {
        /* .iface = */ {
            /* .get_name         = */ ggml_backend_cpu_buffer_type_get_name,
            /* .alloc_buffer     = */ ggml_backend_cpu_buffer_type_alloc_buffer,
            /* .get_alignment    = */ ggml_backend_cpu_buffer_type_get_alignment,
            /* .get_max_size     = */ NULL, // defaults to SIZE_MAX
            /* .get_alloc_size   = */ NULL, // defaults to ggml_nbytes
            /* .is_host          = */ ggml_backend_cpu_buffer_type_is_host,
        },
        /* .context = */ NULL,
    };

    return &ggml_backend_cpu_buffer_type;
}

#ifdef GGML_USE_CPU_HBM

// buffer type HBM

#include <hbwmalloc.h>

GGML_CALL static const char * ggml_backend_cpu_hbm_buffer_type_get_name(ggml_backend_buffer_type_t buft) {
    return "CPU_HBM";

    GGML_UNUSED(buft);
}

GGML_CALL static const char * ggml_backend_cpu_hbm_buffer_get_name(ggml_backend_buffer_t buf) {
    return "CPU_HBM";

    GGML_UNUSED(buf);
}

GGML_CALL static void ggml_backend_cpu_hbm_buffer_free_buffer(ggml_backend_buffer_t buffer) {
    hbw_free(buffer->context);
}

GGML_CALL static ggml_backend_buffer_t ggml_backend_cpu_hbm_buffer_type_alloc_buffer(ggml_backend_buffer_type_t buft, size_t size) {
    //void * ptr = hbw_malloc(size);
    void * ptr;
    int result = hbw_posix_memalign(&ptr, ggml_backend_cpu_buffer_type_get_alignment(buft), size);
    if (result != 0) {
        fprintf(stderr, "failed to allocate HBM buffer of size %zu\n", size);
        return NULL;
    }

    ggml_backend_buffer_t buffer = ggml_backend_cpu_buffer_from_ptr(ptr, size);
    buffer->buft = buft;
    buffer->iface.get_name = ggml_backend_cpu_hbm_buffer_get_name;
    buffer->iface.free_buffer = ggml_backend_cpu_hbm_buffer_free_buffer;

    return buffer;
}

ggml_backend_buffer_type_t ggml_backend_cpu_hbm_buffer_type(void) {
    static struct ggml_backend_buffer_type ggml_backend_cpu_buffer_type_hbm = {
        /* .iface    = */ {
            /* .get_name         = */ ggml_backend_cpu_hbm_buffer_type_get_name,
            /* .alloc_buffer     = */ ggml_backend_cpu_hbm_buffer_type_alloc_buffer,
            /* .get_alignment    = */ ggml_backend_cpu_buffer_type_get_alignment,
            /* .get_max_size     = */ NULL, // defaults to SIZE_MAX
            /* .get_alloc_size   = */ NULL, // defaults to ggml_nbytes
            /* .is_host          = */ ggml_backend_cpu_buffer_type_is_host,
        },
        /* .context  = */ NULL,
    };

    return &ggml_backend_cpu_buffer_type_hbm;
}
#endif

struct ggml_backend_cpu_context {
    int n_threads;
    void * work_data;
    size_t work_size;

    ggml_abort_callback abort_callback;
    void *              abort_callback_data;

    bool moe_expert_prefetch;
};

GGML_CALL static const char * ggml_backend_cpu_name(ggml_backend_t backend) {
    return "CPU";

    GGML_UNUSED(backend);
}

GGML_CALL static void ggml_backend_cpu_free(ggml_backend_t backend) {
    struct ggml_backend_cpu_context * cpu_ctx = (struct ggml_backend_cpu_context *)backend->context;
    free(cpu_ctx->work_data);
    free(cpu_ctx);
    free(backend);
}

GGML_CALL static ggml_backend_buffer_type_t ggml_backend_cpu_get_default_buffer_type(ggml_backend_t backend) {
    return ggml_backend_cpu_buffer_type();

    GGML_UNUSED(backend);
}

struct ggml_backend_plan_cpu {
    struct ggml_cplan cplan;
    struct ggml_cgraph cgraph;
};

GGML_CALL static ggml_backend_graph_plan_t ggml_backend_cpu_graph_plan_create(ggml_backend_t backend, const struct ggml_cgraph * cgraph) {
    struct ggml_backend_cpu_context * cpu_ctx = (struct ggml_backend_cpu_context *)backend->context;

    struct ggml_backend_plan_cpu * cpu_plan = (ggml_backend_plan_cpu *)malloc(sizeof(struct ggml_backend_plan_cpu));

    cpu_plan->cplan = ggml_graph_plan(cgraph, cpu_ctx->n_threads);
    cpu_plan->cgraph = *cgraph; // FIXME: deep copy

    if (cpu_plan->cplan.work_size > 0) {
        cpu_plan->cplan.work_data = (uint8_t *)malloc(cpu_plan->cplan.work_size);
        if (cpu_plan->cplan.work_data == NULL) {
            free(cpu_plan);
            return NULL;
        }
    }

    cpu_plan->cplan.abort_callback      = cpu_ctx->abort_callback;
    cpu_plan->cplan.abort_callback_data = cpu_ctx->abort_callback_data;
    cpu_plan->cplan.moe_expert_prefetch = cpu_ctx->moe_expert_prefetch;

    return cpu_plan;
}

GGML_CALL static void ggml_backend_cpu_graph_plan_free(ggml_backend_t backend, ggml_backend_graph_plan_t plan) {
    struct ggml_backend_plan_cpu * cpu_plan = (struct ggml_backend_plan_cpu *)plan;

    free(cpu_plan->cplan.work_data);
    free(cpu_plan);

    GGML_UNUSED(backend);
}

GGML_CALL static enum ggml_status ggml_backend_cpu_graph_plan_compute(ggml_backend_t backend, ggml_backend_graph_plan_t plan) {
    struct ggml_backend_plan_cpu * cpu_plan = (struct ggml_backend_plan_cpu *)plan;

    return ggml_graph_compute(&cpu_plan->cgraph, &cpu_plan->cplan);

    GGML_UNUSED(backend);
}

GGML_CALL static enum ggml_status ggml_backend_cpu_graph_compute(ggml_backend_t backend, struct ggml_cgraph * cgraph) {
    struct ggml_backend_cpu_context * cpu_ctx = (struct ggml_backend_cpu_context *)backend->context;

    struct ggml_cplan cplan = ggml_graph_plan(cgraph, cpu_ctx->n_threads);

    if (cpu_ctx->work_size < cplan.work_size) {
        free(cpu_ctx->work_data);
        cpu_ctx->work_data = malloc(cplan.work_size);
        if (cpu_ctx->work_data == NULL) {
            cpu_ctx->work_size = 0;
            return GGML_STATUS_ALLOC_FAILED;
        }
        cpu_ctx->work_size = cplan.work_size;
    }
    cplan.work_data = (uint8_t *)cpu_ctx->work_data;

    cplan.abort_callback      = cpu_ctx->abort_callback;
    cplan.abort_callback_data = cpu_ctx->abort_callback_data;
    cplan.moe_expert_prefetch = cpu_ctx->moe_expert_prefetch;

    return ggml_graph_compute(cgraph, &cplan);
}

GGML_CALL static bool ggml_backend_cpu_supports_op(ggml_backend_t backend, const struct ggml_tensor * op) {
    switch (op->op) {
        case GGML_OP_CPY:
            return
                op->type != GGML_TYPE_IQ2_XXS &&
                op->type != GGML_TYPE_IQ2_XS  &&
                op->type != GGML_TYPE_IQ1_S   &&
                op->type != GGML_TYPE_IQ1_M; // missing type_traits.from_float
        case GGML_OP_MUL_MAT:
            return true;
            //return op->src[1]->type == GGML_TYPE_F32 || op->src[1]->type == ggml_internal_get_type_traits(op->src[0]->type).vec_dot_type;
        default:
            return true;
    }

    GGML_UNUSED(backend);
}

GGML_CALL static bool ggml_backend_cpu_supports_buft(ggml_backend_t backend, ggml_backend_buffer_type_t buft) {
    return ggml_backend_buft_is_host(buft);

    GGML_UNUSED(backend);
}

static struct ggml_backend_i cpu_backend_i = {
    /* .get_name                = */ ggml_backend_cpu_name,
    /* .free                    = */ ggml_backend_cpu_free,
    /* .get_default_buffer_type = */ ggml_backend_cpu_get_default_buffer_type,
    /* .set_tensor_async        = */ NULL,
    /* .get_tensor_async        = */ NULL,
    /* .cpy_tensor_async        = */ NULL,
    /* .synchronize             = */ NULL,
    /* .graph_plan_create       = */ ggml_backend_cpu_graph_plan_create,
    /* .graph_plan_free         = */ ggml_backend_cpu_graph_plan_free,
    /* .graph_plan_update       = */ NULL,
    /* .graph_plan_compute      = */ ggml_backend_cpu_graph_plan_compute,
    /* .graph_compute           = */ ggml_backend_cpu_graph_compute,
    /* .supports_op             = */ ggml_backend_cpu_supports_op,
    /* .supports_buft           = */ ggml_backend_cpu_supports_buft,
    /* .offload_op              = */ NULL,
    /* .event_new               = */ NULL,
    /* .event_free              = */ NULL,
    /* .event_record            = */ NULL,
    /* .event_wait              = */ NULL,
    /* .event_synchronize       = */ NULL,
};

static ggml_guid_t ggml_backend_cpu_guid(void) {
    static ggml_guid guid = { 0xaa, 0x67, 0xc7, 0x43, 0x96, 0xe6, 0xa3, 0x8a, 0xe3, 0xaf, 0xea, 0x92, 0x36, 0xbc, 0xfc, 0x89 };
    return &guid;
}

ggml_backend_t ggml_backend_cpu_init(void) {
    struct ggml_backend_cpu_context * ctx = (ggml_backend_cpu_context *)malloc(sizeof(struct ggml_backend_cpu_context));
    if (ctx == NULL) {
        return NULL;
    }

    ctx->n_threads           = GGML_DEFAULT_N_THREADS;
    ctx->work_data           = NULL;
    ctx->work_size           = 0;
    ctx->abort_callback      = NULL;
    ctx->abort_callback_data = NULL;
    ctx->moe_expert_prefetch = false;

    ggml_backend_t cpu_backend = (ggml_backend_t)malloc(sizeof(struct ggml_backend));
    if (cpu_backend == NULL) {
        free(ctx);
        return NULL;
    }

    *cpu_backend = ggml_backend {
        /* .guid      = */ ggml_backend_cpu_guid(),
        /* .interface = */ cpu_backend_i,
        /* .context   = */ ctx
    };
    return cpu_backend;
}

GGML_CALL bool ggml_backend_is_cpu(ggml_backend_t backend) {
    return backend != NULL && ggml_guid_matches(backend->guid, ggml_backend_cpu_guid());
}

void ggml_backend_cpu_set_n_threads(ggml_backend_t backend_cpu, int n_threads) {
    GGML_ASSERT(ggml_backend_is_cpu(backend_cpu));

    struct ggml_backend_cpu_context * ctx = (struct ggml_backend_cpu_context *)backend_cpu->context;
    ctx->n_threads = n_threads;
}

void ggml_backend_cpu_set_moe_expert_prefetch(ggml_backend_t backend_cpu, bool enable) {
    GGML_ASSERT(ggml_backend_is_cpu(backend_cpu));

    struct ggml_backend_cpu_context * ctx = (struct ggml_backend_cpu_context *)backend_cpu->context;
    ctx->moe_expert_prefetch = enable;
}

void ggml_backend_cpu_set_abort_callback(ggml_backend_t backend_cpu, ggml_abort_callback abort_callback, void * abort_callback_data) {
    GGML_ASSERT(ggml_backend_is_cpu(backend_cpu));

    struct ggml_backend_cpu_context * ctx = (struct ggml_backend_cpu_context *)backend_cpu->context;
    ctx->abort_callback = abort_callback;
    ctx->abort_callback_data = abort_callback_data;
}

GGML_CALL ggml_backend_buffer_t ggml_backend_cpu_buffer_from_ptr(void * ptr, size_t size) {
    GGML_ASSERT((uintptr_t)ptr % TENSOR_ALIGNMENT == 0 && "buffer pointer must be aligned");
    return ggml_backend_buffer_init(ggml_backend_cpu_buffer_type(), cpu_backend_buffer_i_from_ptr, ptr, size);
}

GGML_CALL static ggml_backend_t ggml_backend_reg_cpu_init(const char * params, void * user_data) {
    return ggml_backend_cpu_init();

    GGML_UNUSED(params);
    GGML_UNUSED(user_data);
}

// multi-buffer buffer

struct ggml_backend_multi_buffer_context {
    ggml_backend_buffer_t * buffers;
    size_t n_buffers;
};

typedef struct ggml_backend_multi_buffer_context * ggml_backend_multi_buffer_context_t;

GGML_CALL static const char * ggml_backend_multi_buffer_get_name(ggml_backend_buffer_t buffer) {
    ggml_backend_multi_buffer_context_t ctx = (ggml_backend_multi_buffer_context_t) buffer->context;

    return ctx->buffers[0]->iface.get_name(ctx->buffers[0]);
}

GGML_CALL static void ggml_backend_multi_buffer_free_buffer(ggml_backend_buffer_t buffer) {
    ggml_backend_multi_buffer_context_t ctx = (ggml_backend_multi_buffer_context_t) buffer->context;
    for (size_t i = 0; i < ctx->n_buffers; i++) {
        ggml_backend_buffer_free(ctx->buffers[i]);
    }

    free(ctx->buffers);
    free(ctx);
}

GGML_CALL static void ggml_backend_multi_buffer_clear(ggml_backend_buffer_t buffer, uint8_t value) {
    ggml_backend_multi_buffer_context_t ctx = (ggml_backend_multi_buffer_context_t) buffer->context;
    for (size_t i = 0; i < ctx->n_buffers; i++) {
        ggml_backend_buffer_clear(ctx->buffers[i], value);
    }
}

static struct ggml_backend_buffer_i ggml_backend_multi_buffer_context_interface(void) {
    static struct ggml_backend_buffer_i multi_backend_buffer_i = {
        /* .get_name        = */ ggml_backend_multi_buffer_get_name,
        /* .free_buffer     = */ ggml_backend_multi_buffer_free_buffer,
        /* .get_base        = */ NULL,
        /* .init_tensor     = */ NULL,
        /* .memset_tensor   = */ NULL,
        /* .set_tensor      = */ NULL,
        /* .get_tensor      = */ NULL,
        /* .cpy_tensor      = */ NULL,
        /* .clear           = */ ggml_backend_multi_buffer_clear,
        /* .reset           = */ NULL,
    };

    return multi_backend_buffer_i;
}

GGML_CALL ggml_backend_buffer_t ggml_backend_multi_buffer_alloc_buffer(ggml_backend_buffer_t * buffers, size_t n_buffers) {
    ggml_backend_multi_buffer_context_t ctx = (ggml_backend_multi_buffer_context_t) malloc(sizeof(struct ggml_backend_multi_buffer_context));
    ctx->n_buffers = n_buffers;
    ctx->buffers = (ggml_backend_buffer_t *) malloc(n_buffers * sizeof(ggml_backend_buffer_t));

    GGML_ASSERT(ctx->buffers != NULL);

    size_t total_size = 0;
    for (size_t i = 0; i < n_buffers; i++) {
        ctx->buffers[i] = buffers[i];
        total_size += ggml_backend_buffer_get_size(buffers[i]);
    }

    return ggml_backend_buffer_init(buffers[0]->buft, ggml_backend_multi_buffer_context_interface(), ctx, total_size);
}

GGML_CALL bool ggml_backend_buffer_is_multi_buffer(ggml_backend_buffer_t buffer) {
    return buffer->iface.get_name == ggml_backend_multi_buffer_get_name;
}

GGML_CALL void ggml_backend_multi_buffer_set_usage(ggml_backend_buffer_t buffer, enum ggml_backend_buffer_usage usage) {
    GGML_ASSERT(ggml_backend_buffer_is_multi_buffer(buffer));
    ggml_backend_multi_buffer_context_t ctx = (ggml_backend_multi_buffer_context_t) buffer->context;
    for (size_t i = 0; i < ctx->n_buffers; i++) {
        ggml_backend_buffer_set_usage(ctx->buffers[i], usage);
    }
}

// creates a copy of the tensor with the same memory layout
static struct ggml_tensor * ggml_dup_tensor_layout(struct ggml_context * ctx, const struct ggml_tensor * tensor) {
    struct ggml_tensor * dup = ggml_dup_tensor(ctx, tensor);
    for (int i = 0; i < GGML_MAX_DIMS; i++) {
        dup->nb[i] = tensor->nb[i];
    }
    return dup;
}

static bool ggml_is_view_op(enum ggml_op op) {
    return op == GGML_OP_VIEW || op == GGML_OP_RESHAPE || op == GGML_OP_PERMUTE || op == GGML_OP_TRANSPOSE;
}

// scheduler

#ifndef GGML_SCHED_MAX_BACKENDS
#define GGML_SCHED_MAX_BACKENDS 16
#endif

#ifndef GGML_SCHED_MAX_SPLITS
#define GGML_SCHED_MAX_SPLITS 4096
#endif

#ifndef GGML_SCHED_MAX_SPLIT_INPUTS
// Gemma4 with per-layer embeddings and uses up to 32 inputs
#define GGML_SCHED_MAX_SPLIT_INPUTS 32
#endif

#ifndef GGML_SCHED_MAX_COPIES
#define GGML_SCHED_MAX_COPIES 4
#endif

struct ggml_backend_sched_split {
    int backend_id;
    int i_start;
    int i_end;
    struct ggml_tensor * inputs[GGML_SCHED_MAX_SPLIT_INPUTS];
    int n_inputs;
    // graph view of this split
    struct ggml_cgraph graph;
};

struct ggml_backend_sched_tp_info_entry {
    const struct ggml_tensor * key;
    std::vector<uint8_t> data;
};

// A raw snapshot of one root graph input. The same root may be used by more
// than one scheduler split, so its bytes are stored once and the split ids
// identify the Turbo replay steps that must restore it.
struct ggml_backend_sched_tp_graph_input_entry {
    const struct ggml_tensor * key;
    std::vector<uint8_t> data;
    std::vector<int> split_ids;
};

enum ggml_backend_sched_tp_input_source_kind {
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UNKNOWN         = 0,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT     = 1,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_LIVE_WEIGHT     = 2,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_INTERMEDIATE = 3,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_LIVE_CURRENT    = 4,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_LIVE_INPUT   = 5,
    GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_PREPARED_INPUT = 6,
};

struct ggml_backend_sched_tp_input_plan {
    const struct ggml_tensor * key;
    int source_kind;
    int producer_split_id;
};

struct ggml_backend_sched_tp_tensor_meta {
    struct ggml_tensor * tensor;
    enum ggml_type type;
    int64_t ne[GGML_MAX_DIMS];
    size_t nb[GGML_MAX_DIMS];
    void * data;
    ggml_backend_buffer_t buffer;
    struct ggml_tensor * view_src;
    size_t view_offs;
    int flags;
};

struct ggml_backend_sched_tp_node_srcs {
    struct ggml_tensor * node;
    struct ggml_tensor * src[GGML_MAX_SRC];
};

struct ggml_backend_sched_tp_split_graph_snapshot {
    struct ggml_backend_sched_split split;
    int backend_id;
    std::vector<struct ggml_tensor *> inputs;
    std::vector<struct ggml_tensor *> nodes;
    std::vector<struct ggml_tensor *> leafs;
    std::vector<ggml_backend_sched_tp_node_srcs> node_srcs;
};

struct ggml_backend_sched_tp_live_split_snapshot {
    struct ggml_backend_sched_split split;
    std::vector<ggml_backend_sched_tp_node_srcs> node_srcs;
};

struct ggml_backend_sched_tp_saved_ub {
    int turboprefill;
    std::vector<uint8_t> start_slot;
    std::vector<ggml_backend_sched_tp_info_entry> split0_inputs;
    std::vector<std::vector<ggml_backend_sched_tp_info_entry>> prepared_input_banks;
    std::vector<ggml_backend_sched_tp_graph_input_entry> graph_inputs;
    std::vector<std::vector<ggml_backend_sched_tp_info_entry>> info_banks;
    std::vector<std::vector<ggml_backend_sched_tp_info_entry>> live_input_banks;
    std::vector<std::vector<ggml_backend_sched_tp_info_entry>> intermediate_banks;
    std::vector<std::vector<ggml_backend_sched_tp_input_plan>> input_plans;
    std::vector<ggml_backend_sched_tp_split_graph_snapshot> split_graphs;
    std::vector<std::vector<ggml_backend_sched_tp_tensor_meta>> split_metas;
    std::vector<std::unordered_map<const struct ggml_tensor *, size_t>> split_meta_index;
    std::vector<ggml_backend_sched_tp_tensor_meta> metas;
};

enum ggml_backend_sched_tp_phase {
    TP_PHASE_PREPARE_H2D = 0,
    TP_PHASE_COMPUTE     = 1,
    TP_PHASE_STORE       = 2,
};

struct ggml_backend_sched {
    bool is_reset; // true if the scheduler has been reset since the last graph split
    bool is_alloc;

    int n_backends;

    ggml_backend_t backends[GGML_SCHED_MAX_BACKENDS];
    ggml_backend_buffer_type_t bufts[GGML_SCHED_MAX_BACKENDS];
    ggml_gallocr_t galloc;

    // hash map of the nodes in the graph
    struct ggml_hash_set  hash_set;
    int                 * hv_tensor_backend_ids; // [hash_set.size]
    struct ggml_tensor ** hv_tensor_copies;      // [hash_set.size][n_backends][n_copies]

    int * node_backend_ids; // [graph_size]
    int * leaf_backend_ids; // [graph_size]

    int * prev_node_backend_ids; // [graph_size]
    int * prev_leaf_backend_ids; // [graph_size]

    // copy of the graph with modified inputs
    struct ggml_cgraph graph;

    // graph splits
    struct ggml_backend_sched_split * splits;
    int n_splits;
    int splits_capacity;

    size_t max_extra_alloc = 0;

    // pipeline parallelism support
    int n_copies;
    int cur_copy;
    ggml_backend_event_t events[GGML_SCHED_MAX_BACKENDS][GGML_SCHED_MAX_COPIES];
    struct ggml_tensor * graph_inputs[GGML_SCHED_MAX_SPLIT_INPUTS];
    int n_graph_inputs;

    struct ggml_context * ctx;

    ggml_backend_sched_eval_callback callback_eval;
    void * callback_eval_user_data;

    char * context_buffer;
    size_t context_buffer_size;

    std::array<ggml_backend_buffer_t, GGML_SCHED_MAX_BACKENDS> input_memory_bufs = {{ nullptr }};

    uint32_t op_offload[(GGML_OP_COUNT + 31)/32];

    std::vector<std::thread> workers;
    std::vector<ggml_status> statuses;
    std::vector<std::vector<ggml_backend_sched_split*>> backend_splits;
    std::array<bool, GGML_SCHED_MAX_BACKENDS> needs_sync;
    std::array<bool, GGML_SCHED_MAX_BACKENDS> own_cpy;

    bool only_active_experts;
    bool split_mode_graph;
    bool is_async = false;
    bool debug;
    bool has_reduce = false;

    std::vector<uint8_t> * tp_ram_slots;
    int tp_ram_slots_count;
    std::vector<ggml_backend_sched_tp_saved_ub> * tp_saved_ubs;
};

static std::vector<uint8_t> & ggml_backend_sched_tp_ram_slot(ggml_backend_sched_t sched, int slot_id, size_t size) {
    GGML_ASSERT(sched);
    GGML_ASSERT(slot_id >= 0);

    if (slot_id >= sched->tp_ram_slots_count) {
        const int new_count = slot_id + 1;
        auto * new_slots = new std::vector<uint8_t>[new_count];

        for (int i = 0; i < sched->tp_ram_slots_count; ++i) {
            new_slots[i].swap(sched->tp_ram_slots[i]);
        }

        delete[] sched->tp_ram_slots;
        sched->tp_ram_slots = new_slots;
        sched->tp_ram_slots_count = new_count;
    }

    auto & slot = sched->tp_ram_slots[slot_id];
    if (slot.size() < size) {
        slot.resize(size);
    }

    return slot;
}

static void ggml_backend_sched_tp_tensor_get_to_ram(
        ggml_backend_t backend,
        ggml_backend_event_t event,
        const struct ggml_tensor * tensor,
        void * data,
        size_t nbytes) {
    ggml_backend_tensor_get_async(backend, tensor, data, 0, nbytes);

    if (event != nullptr &&
        backend->iface.event_record != nullptr &&
        event->backend->iface.event_synchronize != nullptr) {
        ggml_backend_event_record(event);
        ggml_backend_event_synchronize(event);
    } else {
        ggml_backend_synchronize(backend);
    }
}

static void ggml_backend_sched_tp_tensor_get_to_ram_async(
        ggml_backend_t backend,
        const struct ggml_tensor * tensor,
        void * data,
        size_t nbytes) {
    ggml_backend_tensor_get_async(backend, tensor, data, 0, nbytes);
}

static void ggml_backend_sched_tp_tensor_set_from_ram(
        ggml_backend_t backend,
        struct ggml_tensor * tensor,
        const void * data,
        size_t nbytes) {
    ggml_backend_tensor_set_async(backend, tensor, data, 0, nbytes);
}

static void ggml_backend_sched_tp_copy_via_ram(
        ggml_backend_sched_t sched,
        int slot_id,
        ggml_backend_t input_backend,
        ggml_backend_event_t input_event,
        ggml_backend_t split_backend,
        const struct ggml_tensor * input,
        struct ggml_tensor * input_cpy) {
    GGML_ASSERT(ggml_are_same_layout(input, input_cpy) && "cannot copy tensors with different layouts");

    if (input == input_cpy) {
        return;
    }

    const size_t nbytes = ggml_nbytes(input);

    const bool has_event_wait =
            input_event != nullptr &&
            input_backend != nullptr &&
            input_backend->iface.event_record != nullptr &&
            input_event->backend != nullptr &&
            input_event->backend->iface.event_synchronize != nullptr;
    auto & ram_slot = ggml_backend_sched_tp_ram_slot(sched, slot_id, nbytes);
    ggml_backend_tensor_get_async(input_backend, input, ram_slot.data(), 0, nbytes);
    if (has_event_wait) {
        ggml_backend_event_record(input_event);
        ggml_backend_event_synchronize(input_event);
    } else {
        ggml_backend_synchronize(input_backend);
    }
    ggml_backend_tensor_set_async(split_backend, input_cpy, ram_slot.data(), 0, nbytes);
}

static int ggml_backend_sched_tp_slot_id(int split_id, int input_id) {
    return split_id * GGML_SCHED_MAX_SPLIT_INPUTS + input_id;
}

static std::vector<ggml_backend_sched_tp_saved_ub> & ggml_backend_sched_tp_saved_ubs(ggml_backend_sched_t sched) {
    GGML_ASSERT(sched);
    if (sched->tp_saved_ubs == nullptr) {
        sched->tp_saved_ubs = new std::vector<ggml_backend_sched_tp_saved_ub>();
    }
    return *sched->tp_saved_ubs;
}

static void ggml_backend_sched_tp_capture_tensor_meta(
        std::vector<ggml_backend_sched_tp_tensor_meta> & metas,
        struct ggml_tensor * tensor) {
    if (tensor == nullptr) {
        return;
    }

    for (const auto & meta : metas) {
        if (meta.tensor == tensor) {
            return;
        }
    }

    ggml_backend_sched_tp_tensor_meta meta;
    meta.tensor    = tensor;
    meta.type      = tensor->type;
    meta.data      = tensor->data;
    meta.buffer    = tensor->buffer;
    meta.view_src  = tensor->view_src;
    meta.view_offs = tensor->view_offs;
    meta.flags     = tensor->flags;

    for (int i = 0; i < GGML_MAX_DIMS; ++i) {
        meta.ne[i] = tensor->ne[i];
        meta.nb[i] = tensor->nb[i];
    }

    metas.push_back(meta);
}

static void ggml_backend_sched_tp_apply_tensor_metas(
        const std::vector<ggml_backend_sched_tp_tensor_meta> & metas) {
    for (const auto & meta : metas) {
        struct ggml_tensor * tensor = meta.tensor;
        if (tensor == nullptr) {
            continue;
        }

        tensor->type      = meta.type;
        tensor->data      = meta.data;
        tensor->buffer    = meta.buffer;
        tensor->view_src  = meta.view_src;
        tensor->view_offs = meta.view_offs;
        tensor->flags     = meta.flags;

        for (int i = 0; i < GGML_MAX_DIMS; ++i) {
            tensor->ne[i] = meta.ne[i];
            tensor->nb[i] = meta.nb[i];
        }
    }
}

static void ggml_backend_sched_tp_store_to_ram_slot_async(
        ggml_backend_sched_t sched,
        int slot_id,
        ggml_backend_t src_backend,
        const struct ggml_tensor * src) {
    const size_t nbytes = ggml_nbytes(src);
    auto & ram_slot = ggml_backend_sched_tp_ram_slot(sched, slot_id, nbytes);

    ggml_backend_sched_tp_tensor_get_to_ram_async(src_backend, src, ram_slot.data(), nbytes);
}

static bool ggml_backend_sched_tp_load_from_ram_slot(
        ggml_backend_sched_t sched,
        int slot_id,
        ggml_backend_t dst_backend,
        struct ggml_tensor * dst) {
    const size_t nbytes = ggml_nbytes(dst);
    auto & ram_slot = ggml_backend_sched_tp_ram_slot(sched, slot_id, 0);

    if (ram_slot.size() < nbytes) {
        fprintf(stderr, "%s: staging slot %d is not ready: have %zu bytes, need %zu bytes\n",
                __func__, slot_id, ram_slot.size(), nbytes);
        return false;
    }

    ggml_backend_sched_tp_tensor_set_from_ram(dst_backend, dst, ram_slot.data(), nbytes);

    return true;
}
void ggml_backend_sched_set_op_offload(ggml_backend_sched_t sched, enum ggml_op op, bool on_or_off) {
    int int_op = (int)op;
    if (!sched) return;
    if (int_op < 0 || int_op >= (int)GGML_OP_COUNT) {
        uint32_t mask = on_or_off ? 0xffffffff : 0;
        for (int i = 0; i < (GGML_OP_COUNT + 31)/32; ++i) sched->op_offload[i] = mask;
        return;
    }
    int i = int_op >> 5;
    int j = int_op & 31;
    if (on_or_off) {
        sched->op_offload[i] |= (1u << j);
    } else {
        sched->op_offload[i] &= (~(1u << j));
    }
}

void ggml_backend_sched_set_only_active_experts(ggml_backend_sched_t sched, bool on_or_off) {
    if (!sched) return;
    sched->only_active_experts = on_or_off;
}

void ggml_backend_sched_set_split_mode_graph(ggml_backend_sched_t sched, bool on_or_off, bool async) {
    if (!sched) return;
    sched->split_mode_graph = on_or_off;
    sched->is_async = async;
}

void ggml_backend_sched_set_max_extra_alloc(ggml_backend_sched_t sched, int extra_alloc_MiB) {
    if (!sched) return;
    if (extra_alloc_MiB >= 0) {
        sched->max_extra_alloc = size_t(extra_alloc_MiB)*1024*1024;
    }
}

bool ggml_backend_prefetch_init(int n_threads) {
    if (n_threads <= 0) {
        n_threads = std::max(1, std::min(8, (int) std::thread::hardware_concurrency()));
    }
    ggml_moe_prefetch_set_n_threads(n_threads);
    return ggml_moe_prefetch_enabled();
}

void ggml_backend_prefetch_register_mapping(const void * addr, size_t size) {
    ggml_moe_prefetch_register_mapping(addr, size);
}

void ggml_backend_prefetch_unregister_mapping(const void * addr) {
    ggml_moe_prefetch_unregister_mapping(addr);
}

static inline bool ggml_backend_sched_offload_enabled(ggml_backend_sched_t sched, enum ggml_op op) {
    int int_op = (int)op;
    if (!sched || op < 0 || op >= GGML_OP_COUNT) return false;
    return sched->op_offload[int_op >> 5] & (1u << (int_op & 31));
}

#define hash_id(tensor) ggml_hash_find_or_insert(&sched->hash_set, tensor)
#define tensor_backend_id(tensor) sched->hv_tensor_backend_ids[hash_id(tensor)]
#define tensor_id_copy(id, backend_id, copy_id) sched->hv_tensor_copies[(id) * sched->n_backends * sched->n_copies + (backend_id) * sched->n_copies + (copy_id)]
#define tensor_copy(tensor, backend_id, copy_id) tensor_id_copy(hash_id(tensor), backend_id, copy_id)

// returns the priority of the backend, lower id is higher priority
static int ggml_backend_sched_backend_id(ggml_backend_sched_t sched, ggml_backend_t backend) {
    for (int i = 0; i < sched->n_backends; i++) {
        if (sched->backends[i] == backend) {
            return i;
        }
    }
    return -1;
}

static int ggml_backend_sched_backend_from_buffer(ggml_backend_sched_t sched, const struct ggml_tensor * tensor, const struct ggml_tensor * op) {
    ggml_backend_buffer_t buffer = tensor->buffer;
    if (buffer == NULL) {
        return -1;
    }

    //printf("%s: have %d backends, buffer is %s\n", __func__, sched->n_backends, ggml_backend_buffer_name(buffer));
    // find highest prio backend that supports the buffer type and the op
    for (int i = 0; i < sched->n_backends; i++) {
        //printf("  Checking bacckend %d (%s)\n", i, ggml_backend_name(sched->backends[i]));
        if (ggml_backend_supports_buft(sched->backends[i], buffer->buft) &&
            ggml_backend_supports_op(sched->backends[i], op)) {
            return i;
        }
    }

#ifndef NDEBUG
    fprintf(stderr, "%s: warning: no backend supports op %s with a weight with buffer type %s used in tensor %s, the weight will need to be copied\n",
        __func__, ggml_op_desc(tensor), ggml_backend_buffer_name(buffer), tensor->name);
#endif

    return -1;
}

#if 0
static char causes[GGML_DEFAULT_GRAPH_SIZE*16 + GGML_SCHED_MAX_SPLITS*GGML_SCHED_MAX_SPLIT_INPUTS][128]; // debug only
#define SET_CAUSE(node, ...) sprintf(causes[hash_id(node)], __VA_ARGS__)
#define GET_CAUSE(node) causes[hash_id(node)]
#else
#define SET_CAUSE(node, ...)
#define GET_CAUSE(node) ""
#endif

// returns the backend that should be used for the node based on the current locations
static int ggml_backend_sched_backend_id_from_cur(ggml_backend_sched_t sched, struct ggml_tensor * tensor) {
    // TODO: use supports_op to check if the backend supports the op

    // assign pre-allocated nodes to their backend
    int cur_backend_id = ggml_backend_sched_backend_from_buffer(sched, tensor, tensor);
    if (cur_backend_id != -1) {
        SET_CAUSE(tensor, "1.dst");
        return cur_backend_id;
    }

    // view_src
    if (tensor->view_src != NULL) {
        cur_backend_id = ggml_backend_sched_backend_from_buffer(sched, tensor->view_src, tensor);
        if (cur_backend_id != -1) {
            SET_CAUSE(tensor, "1.vsrc");
            return cur_backend_id;
        }
    }

    // graph input
    if (tensor->flags & GGML_TENSOR_FLAG_INPUT) {
        cur_backend_id = sched->n_backends - 1; // last backend (assumed CPU)
        SET_CAUSE(tensor, "1.inp");
        return cur_backend_id;
    }

    // operations with weights are preferably run on the same backend as the weights
    bool offload_enabled = ggml_backend_sched_offload_enabled(sched, tensor->op);
    for (int i = 0; i < GGML_MAX_SRC; i++) {
        const struct ggml_tensor * src = tensor->src[i];
        if (src == NULL) {
            continue;
        }
        if (src->buffer != NULL && src->buffer->usage == GGML_BACKEND_BUFFER_USAGE_WEIGHTS) {
            int src_backend_id = ggml_backend_sched_backend_from_buffer(sched, src, tensor);
            // check if a backend with higher prio wants to offload the op
            if (offload_enabled && src_backend_id == sched->n_backends - 1) {
                for (int b = 0; b < src_backend_id; b++) {
                    if (ggml_backend_supports_op(sched->backends[b], tensor) && ggml_backend_offload_op(sched->backends[b], tensor)) {
                        SET_CAUSE(tensor, "1.off");
                        return b;
                    }
                }
            }
            SET_CAUSE(tensor, "1.wgt%d", i);
            return src_backend_id;
        }
    }

    return -1;
}

static char * fmt_size(size_t size) {
    static char buffer[128];
    if (size >= 1024*1024) {
        snprintf(buffer, sizeof(buffer), "%zuM", size/1024/1024);
    } else {
        snprintf(buffer, sizeof(buffer), "%zuK", size/1024);
    }
    return buffer;
}

static void ggml_backend_sched_print_assignments(ggml_backend_sched_t sched, struct ggml_cgraph * graph) {
    int cur_split = 0;
    for (int i = 0; i < graph->n_nodes; i++) {
        if (cur_split < sched->n_splits && i == sched->splits[cur_split].i_start) {
            ggml_backend_t split_backend = sched->backends[sched->splits[cur_split].backend_id];
            fprintf(stderr, "\n## SPLIT #%d: %s # %d inputs: ", cur_split, ggml_backend_name(split_backend),
                sched->splits[cur_split].n_inputs);
            for (int j = 0; j < sched->splits[cur_split].n_inputs; j++) {
                fprintf(stderr, "[%s (%5.5s)] ", sched->splits[cur_split].inputs[j]->name,
                    fmt_size(ggml_nbytes(sched->splits[cur_split].inputs[j])));
            }
            fprintf(stderr, "\n");
            cur_split++;
        }
        struct ggml_tensor * node = graph->nodes[i];
        if (ggml_is_view_op(node->op)) {
            continue;
        }
        ggml_backend_t tensor_backend = ggml_backend_sched_get_tensor_backend(sched, node);
        fprintf(stderr, "node #%3d (%10.10s): %20.20s (%5.5s) [%5.5s %8.8s]:", i, ggml_op_name(node->op), node->name,
            fmt_size(ggml_nbytes(node)), tensor_backend ? ggml_backend_name(tensor_backend) : "NULL", GET_CAUSE(node));
        for (int j = 0; j < GGML_MAX_SRC; j++) {
            struct ggml_tensor * src = node->src[j];
            if (src == NULL) {
                continue;
            }
            ggml_backend_t src_backend = ggml_backend_sched_get_tensor_backend(sched, src);
            fprintf(stderr, " %20.20s (%5.5s) [%5.5s %8.8s]", src->name,
                fmt_size(ggml_nbytes(src)), src_backend ? ggml_backend_name(src_backend) : "NULL", GET_CAUSE(src));
        }
        fprintf(stderr, "\n");
    }
}

static bool ggml_backend_sched_buffer_supported(ggml_backend_sched_t sched, struct ggml_tensor * t, int backend_id) {
    ggml_backend_buffer_t buf = t->view_src ? t->view_src->buffer : t->buffer;
    ggml_backend_buffer_type_t buft = NULL;

    if (buf) {
        // the tensor is already allocated
        buft = buf->buft;
    } else {
        // see if the tensor already has a backend assigned, and use the buffer type of that backend
        int tensor_backend_id = tensor_backend_id(t);
        if (tensor_backend_id == -1 && t->view_src) {
            tensor_backend_id = tensor_backend_id(t->view_src);
        }
        if (tensor_backend_id != -1) {
            buft = sched->bufts[tensor_backend_id];
        }
    }

    return buft != NULL && ggml_backend_supports_buft(sched->backends[backend_id], buft);
}

static void ggml_backend_sched_set_if_supported(ggml_backend_sched_t sched, struct ggml_tensor * node, int cur_backend_id, int * node_backend_id) {
    if (ggml_backend_supports_op(sched->backends[cur_backend_id], node)) {
        *node_backend_id = cur_backend_id;
        SET_CAUSE(node, "2.sup");
    }
}

// assigns backends to ops and splits the graph into subgraphs that can be computed on the same backend
static void ggml_backend_sched_split_graph(ggml_backend_sched_t sched, struct ggml_cgraph * graph) {
    // reset splits
    sched->n_splits = 0;
    sched->n_graph_inputs = 0;
    sched->is_reset = false;
    sched->has_reduce = false;

    struct ggml_init_params params = {
        /* .mem_size =   */ sched->context_buffer_size,
        /* .mem_buffer = */ sched->context_buffer,
        /* .no_alloc =   */ true
    };

    ggml_free(sched->ctx);

    sched->ctx = ggml_init(params);
    if (sched->ctx == NULL) {
        GGML_ABORT("%s: failed to initialize context\n", __func__);
    }

    // pass 1: assign backends to ops with pre-allocated inputs
    for (int i = 0; i < graph->n_leafs; i++) {
        struct ggml_tensor * leaf = graph->leafs[i];
        int * leaf_backend_id = &tensor_backend_id(leaf);
        // do not overwrite user assignments
        if (*leaf_backend_id == -1) {
            *leaf_backend_id = ggml_backend_sched_backend_id_from_cur(sched, leaf);
        }
    }

    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        int * node_backend_id = &tensor_backend_id(node);
        if (node->op == GGML_OP_REDUCE) {
            auto view_src = node->view_src;
            int src_id = -1;
            for (int j = 0; j < node->op_params[1]; ++j) {
                if (node->src[j]) {
                    int * this_node_backend_id = &tensor_backend_id(node->src[j]);
                    if (*this_node_backend_id == -1) {
                        *this_node_backend_id = j;
                    } else {
                        GGML_ASSERT(*this_node_backend_id == j);
                    }
                    if (view_src == node->src[j]) {
                        src_id = j;
                    }
                }
            }
            if (src_id >= 0) {
                int * this_node_backend_id = &tensor_backend_id(view_src);
                *this_node_backend_id = tensor_backend_id(node->src[src_id]);
                *node_backend_id = *this_node_backend_id;
            }
        }
        else if (node->op == GGML_OP_MUL && node->src[0]->op == GGML_OP_NORM) {
            // This is a hack for Cohere2. Without this hack the scheduler creates
            // totally nonsensical splits for that arch
            int * src1_id = &tensor_backend_id(node->src[1]);
            if (*src1_id >= 0) {
                int * src0_id = &tensor_backend_id(node->src[0]);
                int * dst_id  = &tensor_backend_id(node);
                *src0_id = *src1_id;
                *dst_id  = *src1_id;
                // For some reason that I don't understand, we can have norm backend already assigned
                // at this point. How? That's why this more logical approach of first checking is commented out
                //if (*src0_id < 0) {
                //    *src0_id = *src1_id;
                //} else {
                //    printf("Oops: backend_id_src0(%s) = %d, backend_id_src1(%s) = %d\n", node->src[0]->name, *src0_id, node->src[1]->name, *src1_id);
                //    //GGML_ASSERT(*src0_id == *src1_id);
                //}
                //if (*dst_id < 0) {
                //    *dst_id = *src1_id;
                //} else {
                //    printf("Oops: backend_id_dst(%s) = %d, backend_id_src1(%s) = %d\n", node->name, *dst_id, node->src[1]->name, *src1_id);
                //    //GGML_ASSERT(*dst_id == *src1_id);
                //}
            }
        }
        // do not overwrite user assignments
        if (*node_backend_id == -1) {
            *node_backend_id = ggml_backend_sched_backend_id_from_cur(sched, node);
            //printf("Pass 1: assigned backend %d to node %d, %s(%s)\n", *node_backend_id, i, ggml_op_name(node->op), node->name);

#if 0
            // src
            if (node->op == GGML_OP_NONE) {
                continue;
            }

            for (int j = 0; j < GGML_MAX_SRC; j++) {
                struct ggml_tensor * src = node->src[j];
                if (src == NULL) {
                    continue;
                }
                int * src_backend_id = &tensor_backend_id(src);
                if (*src_backend_id == -1) {
                    *src_backend_id = ggml_backend_sched_backend_id_from_cur(sched, src);
                }
            }
#endif
        }
    }

    // pass 2: expand current backend assignments
    // assign the same backend to adjacent nodes
    // expand gpu backends (i.e. non last prio) up and down, ignoring cpu (the lowest priority backend)
    // thus, cpu will never be used unless weights are on cpu, or there are no gpu ops between cpu ops
    // ops unsupported by the backend being expanded will be left unassigned so that they can be assigned later when the locations of its inputs are known
    // expand gpu down
    {
        int cur_backend_id = -1;
        for (int i = 0; i < graph->n_nodes; i++) {
            struct ggml_tensor * node = graph->nodes[i];
            if (ggml_is_view_op(node->op)) {
                continue;
            }
            int * node_backend_id = &tensor_backend_id(node);
            if (*node_backend_id != -1) {
                if (*node_backend_id == sched->n_backends - 1) {
                    // skip cpu (lowest prio backend)
                    cur_backend_id = -1;
                } else {
                    cur_backend_id = *node_backend_id;
                }
            } else if (cur_backend_id != -1) {
                //printf("(u1) invoking ggml_backend_sched_set_if_supported for node %d, %s with cur_backend_id = %d, node_backend_id = %d\n", i, node->name, cur_backend_id, *node_backend_id);
                ggml_backend_sched_set_if_supported(sched, node, cur_backend_id, node_backend_id);
            }
        }
    }
    // expand gpu up
    {
        int cur_backend_id = -1;
        for (int i = graph->n_nodes - 1; i >= 0; i--) {
            struct ggml_tensor * node = graph->nodes[i];
            if (ggml_is_view_op(node->op)) {
                continue;
            }
            int * node_backend_id = &tensor_backend_id(node);
            if (*node_backend_id != -1) {
                if (*node_backend_id == sched->n_backends - 1) {
                    // skip cpu (lowest prio backend)
                    cur_backend_id = -1;
                } else {
                    cur_backend_id = *node_backend_id;
                }
            } else if (cur_backend_id != -1) {
                //printf("(d1) invoking ggml_backend_sched_set_if_supported for node %d, %s with cur_backend_id = %d, node_backend_id = %d\n", i, node->name, cur_backend_id, *node_backend_id);
                ggml_backend_sched_set_if_supported(sched, node, cur_backend_id, node_backend_id);
            }
        }
    }
    // expand rest down
    {
        int cur_backend_id = -1;
        for (int i = 0; i < graph->n_nodes; i++) {
            struct ggml_tensor * node = graph->nodes[i];
            if (ggml_is_view_op(node->op)) {
                continue;
            }
            int * node_backend_id = &tensor_backend_id(node);
            if (*node_backend_id != -1) {
                cur_backend_id = *node_backend_id;
            } else if (cur_backend_id != -1) {
                //printf("(u2) invoking ggml_backend_sched_set_if_supported for node %d, %s with cur_backend_id = %d, node_backend_id = %d\n", i, node->name, cur_backend_id, *node_backend_id);
                ggml_backend_sched_set_if_supported(sched, node, cur_backend_id, node_backend_id);
            }
        }
    }
    // expand rest up
    {
        int cur_backend_id = -1;
        for (int i = graph->n_nodes - 1; i >= 0; i--) {
            struct ggml_tensor * node = graph->nodes[i];
            if (ggml_is_view_op(node->op)) {
                continue;
            }
            int * node_backend_id = &tensor_backend_id(node);
            if (*node_backend_id != -1) {
                cur_backend_id = *node_backend_id;
            } else if (cur_backend_id != -1) {
                //printf("(d2) invoking ggml_backend_sched_set_if_supported for node %d, %s with cur_backend_id = %d, node_backend_id = %d\n", i, node->name, cur_backend_id, *node_backend_id);
                ggml_backend_sched_set_if_supported(sched, node, cur_backend_id, node_backend_id);
            }
        }
    }

    // pass 3: upgrade nodes to higher prio backends with compatible buffer types
    // if the tensor is already in the same buffer type (*) as another higher priority backend, we should move it there
    // however, we also need to verify that the sources are in compatible buffer types
    // (*) the actual requirement is more relaxed, the buffer type of the backend should be supported by all the users of this tensor further down the graph
    // however, this is slow to verify, so we have a more strict requirement that the buffer type is the same
    // this is not uncommon since multiple backends can use host memory, with the same buffer type (eg. BLAS and CPU)
    // additionally, set remaining unassigned nodes to the backend with the most supported inputs
    // only nodes that could not be assigned during expansion due to the backend not supporting the op should be unassigned at this point
    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        if (ggml_is_view_op(node->op)) {
            continue;
        }
        int * node_backend_id = &tensor_backend_id(node);
        if (*node_backend_id == -1) {
            // unassigned node: find the backend with the most supported inputs
            int n_supported_best = -1;
            for (int b = 0; b < sched->n_backends; b++) {
                if (ggml_backend_supports_op(sched->backends[b], node)) {
                    int n_supported = 0;
                    for (int j = 0; j < GGML_MAX_SRC; j++) {
                        struct ggml_tensor * src = node->src[j];
                        if (src == NULL) {
                            continue;
                        }
                        if ((tensor_backend_id(src) != -1 || tensor_backend_id(src->view_src) != -1) && ggml_backend_sched_buffer_supported(sched, src, b)) {
                            n_supported++;
                        }
                    }
                    if (n_supported > n_supported_best) {
                        n_supported_best = n_supported;
                        *node_backend_id = b;
                        //printf("Pass 3: assigned backend %d to unassigned node %d, %s\n", b, i, node->name);
                        SET_CAUSE(node, "3.best");
                    }
                }
            }
        } else {
            // assigned node: upgrade to higher prio backend if possible
            for (int b = 0; b < *node_backend_id; b++) {
                if (sched->bufts[b] == sched->bufts[*node_backend_id] && ggml_backend_supports_op(sched->backends[b], node)) {
                    bool supported = true;
                    for (int j = 0; j < GGML_MAX_SRC; j++) {
                        struct ggml_tensor * src = node->src[j];
                        if (src == NULL) {
                            continue;
                        }
                        if (!ggml_backend_sched_buffer_supported(sched, src, b)) {
                            supported = false;
                            break;
                        }
                    }
                    if (supported) {
                        //printf("Pass 3: assigned backend %d to node %d, %s previously assigned to backend %d\n", b, i, node->name, *node_backend_id);
                        *node_backend_id = b;
                        SET_CAUSE(node, "3.upg");
                        break;
                    }
                }
            }
        }
    }

    // pass 4: assign backends to remaining src from dst and view_src
    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        int * cur_backend_id = &tensor_backend_id(node);
        if (node->view_src != NULL && *cur_backend_id == -1) {
            *cur_backend_id = tensor_backend_id(node->view_src);
            SET_CAUSE(node, "4.vsrc");
        }
        for (int j = 0; j < GGML_MAX_SRC; j++) {
            struct ggml_tensor * src = node->src[j];
            if (src == NULL) {
                continue;
            }
            int * src_backend_id = &tensor_backend_id(src);
            if (*src_backend_id == -1) {
                if (src->view_src != NULL) {
                    // views are always on the same backend as the source
                    *src_backend_id = tensor_backend_id(src->view_src);
                    SET_CAUSE(src, "4.vsrc");
                    //printf("Pass 4: assigned backend %d to src %d, %s in node %d, %s frpm view_src\n", *src_backend_id, j, src->name, i, node->name);
                } else {
                    *src_backend_id = *cur_backend_id;
                    SET_CAUSE(src, "4.cur");
                    //printf("Pass 4: assigned backend %d to src %d, %s in node %d, %s frpm current\n", *src_backend_id, j, src->name, i, node->name);
                }
            }
        }
    }

    // pass 5: split graph, find tensors that need to be copied
    {
        int i_split = 0;
        struct ggml_backend_sched_split * split = &sched->splits[0];
        // find the backend of the first split, skipping view ops
        int i = 0;
        for (; i < graph->n_nodes; i++) {
            struct ggml_tensor * node = graph->nodes[i];
            if (!ggml_is_view_op(node->op)) {
                split->backend_id = tensor_backend_id(node);
                break;
            }
        }
        split->i_start = 0;
        split->n_inputs = 0;
        int cur_backend_id = split->backend_id;
        for (; i < graph->n_nodes; i++) {
            struct ggml_tensor * node = graph->nodes[i];

            if (ggml_is_view_op(node->op)) {
                continue;
            }

            const int node_backend_id = tensor_backend_id(node);

            assert(node_backend_id != -1); // all nodes should be assigned by now

            // check if we should start a new split based on the sources of the current node
            bool need_new_split = false;
            if (node->op == GGML_OP_REDUCE) {
                sched->has_reduce = true;
            }
            if ((node->op == GGML_OP_ADD && node->op_params[0] == 0xff) ||
                 node->op == GGML_OP_REDUCE ||
                 node->op == GGML_OP_FAKE_CPY ||
                 node->op_params[GGML_MAX_OP_PARAMS / sizeof(int32_t) - 1] == 0xff) {
                need_new_split = true;
            }
            else if (node_backend_id == cur_backend_id && split->n_inputs > 0) {
                for (int j = 0; j < GGML_MAX_SRC; j++) {
                    struct ggml_tensor * src = node->src[j];
                    if (src == NULL) {
                        continue;
                    }
                    // check if a weight is on a different backend
                    // by starting a new split, the memory of the previously offloaded weights can be reused
                    if (src->buffer != NULL && src->buffer->usage == GGML_BACKEND_BUFFER_USAGE_WEIGHTS) {
                        int src_backend_id = tensor_backend_id(src);
                        if (src_backend_id != cur_backend_id) {
                            need_new_split = true;
                            break;
                        }
                    }
                    // check if the split has too many inputs
                    // FIXME: count the number of inputs instead of only checking when full
                    if (split->n_inputs == GGML_SCHED_MAX_SPLIT_INPUTS) {
                        const size_t id = hash_id(src);
                        int src_backend_id = sched->hv_tensor_backend_ids[id];
                        bool supported = ggml_backend_sched_buffer_supported(sched, src, cur_backend_id);
                        if (src_backend_id != cur_backend_id && tensor_id_copy(id, cur_backend_id, 0) == NULL && !supported) {
                            //printf("starting new split because of too many inputs: node %s, input %s\n", node->name, src->name);
                            need_new_split = true;
                            break;
                        }
                    }
                }
            }

            if (node_backend_id != cur_backend_id || need_new_split) {
                split->i_end = i;
                i_split++;
                if (i_split >= sched->splits_capacity) {
                    sched->splits_capacity *= 2;
                    sched->splits = (ggml_backend_sched_split *)realloc(sched->splits, sched->splits_capacity * sizeof(struct ggml_backend_sched_split));
                    GGML_ASSERT(sched->splits != NULL);
                }
                GGML_ASSERT(i_split < GGML_SCHED_MAX_SPLITS);
                split = &sched->splits[i_split];
                split->backend_id = node_backend_id;
                split->i_start = i;
                split->n_inputs = 0;
                cur_backend_id = node_backend_id;
            }

            // find inputs that are not on the same backend
            for (int j = 0; j < GGML_MAX_SRC; j++) {
                struct ggml_tensor * src = node->src[j];
                if (src == NULL) {
                    continue;
                }

                size_t src_id = hash_id(src);
                const int src_backend_id = sched->hv_tensor_backend_ids[src_id];
                assert(src_backend_id != -1); // all inputs should be assigned by now

                if (src->flags & GGML_TENSOR_FLAG_INPUT && sched->n_copies > 1) {
                    if (tensor_id_copy(src_id, src_backend_id, 0) == NULL) {
                        ggml_backend_t backend = sched->backends[src_backend_id];
                        for (int c = 0; c < sched->n_copies; c++) {
                            struct ggml_tensor * tensor_copy;
                            if (c == sched->cur_copy) {
                                tensor_copy = src; // use the original tensor as the current copy
                            } else {
                                tensor_copy = ggml_dup_tensor_layout(sched->ctx, src);
                                ggml_format_name(tensor_copy, "%s#%s#%d", ggml_backend_name(backend), src->name, c);
                            }
                            if (sched->n_copies > 1) {
                                ggml_set_input(tensor_copy);
                                ggml_set_output(tensor_copy); // prevent ggml-alloc from overwriting the tensor
                            }
                            tensor_id_copy(src_id, src_backend_id, c) = tensor_copy;
                            SET_CAUSE(tensor_copy, "4.cpy");
                        }
                        int n_graph_inputs = sched->n_graph_inputs++;
                        GGML_ASSERT(n_graph_inputs < GGML_SCHED_MAX_SPLIT_INPUTS);
                        sched->graph_inputs[n_graph_inputs] = src;
                    }
                }

                if (src_backend_id != cur_backend_id && !ggml_backend_sched_buffer_supported(sched, src, cur_backend_id)) {
                    // create a copy of the input in the split's backend
                    if (tensor_id_copy(src_id, cur_backend_id, 0) == NULL) {
                        if (node->op == GGML_OP_REDUCE) {
                            //printf("setting tensor_id_copy(reduce, %zu, %d, %s) to %s\n", src_id, cur_backend_id, node->name, src->name);
                            tensor_id_copy(src_id, cur_backend_id, 0) = src;
                        } else if (node->op == GGML_OP_FAKE_CPY && src->op == GGML_OP_REDUCE) {
                            //printf("setting tensor_id_copy(fake_cpy, %zu, %d, %s) to %s\n", src_id, cur_backend_id, node->name, src->src[j]->name);
                            tensor_id_copy(src_id, cur_backend_id, 0) = src->src[j];
                        } else {
                        ggml_backend_t backend = sched->backends[cur_backend_id];
                        for (int c = 0; c < sched->n_copies; c++) {
                            struct ggml_tensor * tensor_copy = ggml_dup_tensor_layout(sched->ctx, src);
                            ggml_format_name(tensor_copy, "%s#%s#%d", ggml_backend_name(backend), src->name, c);
                            if (sched->n_copies > 1) {
                                ggml_set_input(tensor_copy);
                                ggml_set_output(tensor_copy); // prevent ggml-alloc from overwriting the tensor
                            }
                            tensor_id_copy(src_id, cur_backend_id, c) = tensor_copy;
                            SET_CAUSE(tensor_copy, "4.cpy");
                        }
                        int n_inputs = split->n_inputs++;
                        if (n_inputs >= GGML_SCHED_MAX_SPLIT_INPUTS) {
                            printf("======================== Oops, too many inputs (%d)\n", n_inputs+1);
                            for (int k = 0; k < n_inputs; ++k) printf("Input %2d: %s\n", k, split->inputs[k]->name);
                        }
                        GGML_ASSERT(n_inputs < GGML_SCHED_MAX_SPLIT_INPUTS);
                        split->inputs[n_inputs] = src;
                        }
                    }
                    node->src[j] = tensor_id_copy(src_id, cur_backend_id, sched->cur_copy);
                }
            }
        }
        split->i_end = graph->n_nodes;
        sched->n_splits = i_split + 1;
    }

    if (sched->debug) {
        ggml_backend_sched_print_assignments(sched, graph);
    }

    // swap node_backend_ids and leaf _backend_ids with prevs
    {
        int * tmp = sched->node_backend_ids;
        sched->node_backend_ids = sched->prev_node_backend_ids;
        sched->prev_node_backend_ids = tmp;

        tmp = sched->leaf_backend_ids;
        sched->leaf_backend_ids = sched->prev_leaf_backend_ids;
        sched->prev_leaf_backend_ids = tmp;
    }

    int graph_size = graph->n_nodes + sched->n_splits*GGML_SCHED_MAX_SPLIT_INPUTS*2;
    if (sched->graph.size < graph_size) {
        sched->graph.size = graph_size;
        sched->graph.nodes = (ggml_tensor **)realloc(sched->graph.nodes, graph_size * sizeof(struct ggml_tensor *));
        sched->graph.leafs = (ggml_tensor **)realloc(sched->graph.leafs, graph_size * sizeof(struct ggml_tensor *));
        GGML_ASSERT(sched->graph.nodes != NULL);
        GGML_ASSERT(sched->graph.leafs != NULL);
    }
    sched->graph.n_nodes = 0;
    sched->graph.n_leafs = 0;

    struct ggml_cgraph * graph_copy = &sched->graph;

    for (int i = 0; i < sched->n_splits; i++) {
        struct ggml_backend_sched_split * split = &sched->splits[i];
        split->graph = ggml_graph_view(graph, split->i_start, split->i_end);

        // add inputs to the graph copy so that they are allocated by ggml-alloc at the start of the split
        for (int j = 0; j < split->n_inputs; j++) {
            assert(graph_copy->size > (graph_copy->n_nodes + 1));

            struct ggml_tensor * input = split->inputs[j];
            const size_t input_id = hash_id(input);
            struct ggml_tensor * input_cpy = tensor_id_copy(input_id, split->backend_id, sched->cur_copy);

            // add a dependency to the input source so that it is not freed before the copy is done
            struct ggml_tensor * input_dep = ggml_view_tensor(sched->ctx, input);
            input_dep->src[0] = input;
            sched->node_backend_ids[graph_copy->n_nodes] = sched->hv_tensor_backend_ids[input_id];
            graph_copy->nodes[graph_copy->n_nodes++] = input_dep;

            // add a dependency to the input copy so that it is allocated at the start of the split
            sched->node_backend_ids[graph_copy->n_nodes] = split->backend_id;
            graph_copy->nodes[graph_copy->n_nodes++] = input_cpy;
        }

        for (int j = split->i_start; j < split->i_end; j++) {
            assert(graph_copy->size > graph_copy->n_nodes);
            sched->node_backend_ids[graph_copy->n_nodes] = tensor_backend_id(graph->nodes[j]);
            graph_copy->nodes[graph_copy->n_nodes++] = graph->nodes[j];
        }
    }

    if (sched->n_copies > 1) {
        // add input copies as leafs so that they are allocated first
        for (int i = 0; i < sched->n_graph_inputs; i++) {
            struct ggml_tensor * input = sched->graph_inputs[i];
            size_t id = hash_id(input);
            int backend_id = tensor_backend_id(input);
            for (int c = 0; c < sched->n_copies; c++) {
                struct ggml_tensor * input_cpy = tensor_id_copy(id, backend_id, c);
                sched->leaf_backend_ids[graph_copy->n_leafs] = backend_id;
                graph_copy->leafs[graph_copy->n_leafs++] = input_cpy;
            }
        }

        for (int i = 0; i < sched->n_splits; i++) {
            struct ggml_backend_sched_split * split = &sched->splits[i];
            int backend_id = split->backend_id;
            for (int j = 0; j < split->n_inputs; j++) {
                struct ggml_tensor * input = split->inputs[j];
                size_t id = hash_id(input);
                for (int c = 0; c < sched->n_copies; c++) {
                    struct ggml_tensor * input_cpy = tensor_id_copy(id, backend_id, c);
                    sched->leaf_backend_ids[graph_copy->n_leafs] = backend_id;
                    graph_copy->leafs[graph_copy->n_leafs++] = input_cpy;
                }
            }
        }
    }

    // add leafs from the original graph
    for (int i = 0; i < graph->n_leafs; i++) {
        struct ggml_tensor * leaf = graph->leafs[i];
        sched->leaf_backend_ids[graph_copy->n_leafs] = tensor_backend_id(leaf);
        graph_copy->leafs[graph_copy->n_leafs++] = leaf;
    }
}

static bool ggml_backend_sched_alloc_splits(ggml_backend_sched_t sched) {
    bool backend_ids_changed = false;
    for (int i = 0; i < sched->graph.n_nodes; i++) {
        if (sched->node_backend_ids[i] != sched->prev_node_backend_ids[i] &&
            sched->bufts[sched->node_backend_ids[i]] != sched->bufts[sched->prev_node_backend_ids[i]]) {
            backend_ids_changed = true;
            break;
        }
    }
    if (!backend_ids_changed) {
        for (int i = 0; i < sched->graph.n_leafs; i++) {
            if (sched->leaf_backend_ids[i] != sched->prev_leaf_backend_ids[i] &&
                sched->bufts[sched->leaf_backend_ids[i]] != sched->bufts[sched->prev_leaf_backend_ids[i]]) {
                backend_ids_changed = true;
                break;
            }
        }
    }

    // allocate graph
    if (backend_ids_changed || !ggml_gallocr_alloc_graph(sched->galloc, &sched->graph)) {
        // the re-allocation may cause the split inputs to be moved to a different address
        ggml_backend_sched_synchronize(sched);
#ifndef NDEBUG
        fprintf(stderr, "%s: failed to allocate graph, reserving (backend_ids_changed = %d)\n", __func__, backend_ids_changed);
#endif
        ggml_gallocr_reserve_n(sched->galloc, &sched->graph, sched->node_backend_ids, sched->leaf_backend_ids);
        if (!ggml_gallocr_alloc_graph(sched->galloc, &sched->graph)) {
            fprintf(stderr, "%s: failed to allocate graph\n", __func__);
            return false;
        }
    }

    return true;
}

static void ggml_backend_sched_copy_inputs(ggml_backend_sched_t sched, ggml_backend_sched_split * split, std::array<bool, GGML_SCHED_MAX_BACKENDS> & needs_sync,
        std::vector<int32_t> & ids, std::vector<uint32_t> & unique_ids, ggml_tensor * last_ids_tensor) {
    if (split->n_inputs < 1) return;
    constexpr bool k_set_sync = false;
    int split_backend_id = split->backend_id;
    ggml_backend_t split_backend = sched->backends[split_backend_id];
    ggml_backend_t last_input_backend = nullptr;
    bool synced_on_input = false;
    for (int j = 0; j < split->n_inputs; j++) {
        ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, split->inputs[j]);
        struct ggml_tensor * input = split->inputs[j];
        struct ggml_tensor * input_cpy = tensor_copy(input, split_backend_id, sched->cur_copy);

        if (input->flags & GGML_TENSOR_FLAG_INPUT) {
            // inputs from the user must be copied immediately to prevent the user overwriting the data before the copy is done
            // if there are multiple inputs for the split, and we have already synchronized this backend, no need to do it again.
            if (!synced_on_input) {
                if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                    ggml_backend_event_synchronize(sched->events[split_backend_id][sched->cur_copy]);
                } else {
                    ggml_backend_synchronize(split_backend);
                }
                synced_on_input = true;
            }
            ggml_backend_tensor_copy(input, input_cpy);
        } else {
            // wait for the split backend to finish using the input before overwriting it
            if (needs_sync[split_backend_id]) {
                if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                    ggml_backend_event_wait(split_backend, sched->events[split_backend_id][sched->cur_copy]);
                } else {
                    ggml_backend_synchronize(split_backend);
                }
                needs_sync[split_backend_id] = k_set_sync;
            }

            ggml_tensor * node = split->graph.nodes[0];
            if (sched->only_active_experts && split->graph.n_nodes > 0 &&
                    ggml_backend_buffer_get_usage(input->buffer) == GGML_BACKEND_BUFFER_USAGE_WEIGHTS &&
                    ggml_backend_buffer_is_host(input->buffer) &&
                    (node->op == GGML_OP_MUL_MAT_ID || node->op == GGML_OP_MOE_FUSED_UP_GATE)) {

                if (input_backend != last_input_backend) {
                    ggml_backend_synchronize(input_backend);
                    last_input_backend = input_backend;
                }

                ggml_tensor * ids_tensor = node->op == GGML_OP_MUL_MAT_ID ? node->src[2] : node->src[3];
                auto ids_backend = split_backend;

                // if the ids tensor is also an input of the split, it may not have been copied yet to the split backend
                // in that case, we use the original ids tensor
                for (int jj = j + 1; jj < split->n_inputs; ++jj) {
                    if (ids_tensor == tensor_copy(split->inputs[jj], split_backend_id, sched->cur_copy)) {
                        ids_tensor = split->inputs[jj];
                        ids_backend = ggml_backend_sched_get_tensor_backend(sched, split->inputs[jj]);
                        break;
                    }
                }

                int n_expert = node->src[0]->ne[2];

                if (ids_tensor != last_ids_tensor) {
                    ids.resize(ggml_nbytes(ids_tensor) / sizeof(int32_t));

                    ggml_backend_tensor_get_async(ids_backend, ids_tensor, ids.data(), 0, ggml_nbytes(ids_tensor));

                    ggml_backend_synchronize(ids_backend);
                    if (auto id = tensor_backend_id(ids_tensor); id >= 0 && id < GGML_SCHED_MAX_BACKENDS) {
                        needs_sync[id] = k_set_sync;
                    }
                    //needs_sync[tensor_backend_id(ids_tensor)] = k_set_sync;

                    unique_ids.resize((n_expert + 31)/32);
                    std::memset(unique_ids.data(), 0, unique_ids.size()*sizeof(uint32_t));
                    for (int64_t i1 = 0; i1 < ids_tensor->ne[1]; i1++) {
                        for (int64_t i0 = 0; i0 < ids_tensor->ne[0]; i0++) {
                            int32_t id = ids[i1 * ids_tensor->nb[1]/sizeof(int32_t) + i0 * ids_tensor->nb[0]/sizeof(int32_t)];
                            unique_ids[id >> 5] |= (1u << (id & 31));
                        }
                    }

                    last_ids_tensor = ids_tensor;
                }

                // when the expert prefetch engine streamed this tensor ahead
                // (see the lookahead in compute_splits), wait for it so the
                // host-side reads below hit warm page cache instead of faulting
                ggml_moe_prefetch_wait(input);

                const size_t expert_size = input->ne[2] > 1 ? input->nb[2] : input->nb[1];

                if (input->ne[2] > 1) {

                    auto copy_experts = [&](int32_t first_id, int32_t last_id) {
                        const size_t expert_offset = first_id * expert_size;
                        const size_t expert_size_copy =  (last_id - first_id + 1) * expert_size;
                        const size_t padding = 512;
                        const size_t padding_end = last_id < n_expert - 1 ? std::min<size_t>(expert_size, padding) : 0;

                        ggml_backend_tensor_set_async(split_backend,
                                input_cpy,
                                (const uint8_t *)input->data + expert_offset, expert_offset,
                                // copy a bit extra to ensure there are no NaNs in the padding
                                expert_size_copy + padding_end);

                    };

                    auto next_on_id = [&unique_ids, n_expert] (int id) {
                        while (id < n_expert && (unique_ids[id >> 5] & (1u << (id & 31))) == 0) ++id;
                        return id;
                    };
                    auto next_off_id = [&unique_ids, n_expert] (int id) {
                        while (id < n_expert && (unique_ids[id >> 5] & (1u << (id & 31))) != 0) ++id;
                        return id;
                    };

                    int first_id = next_on_id(0);
                    while (first_id < n_expert) {
                        int last_id = next_off_id(first_id+1);
                        copy_experts(first_id, last_id-1);
                        first_id = next_on_id(last_id);
                    }

                } else {
                    auto copy_size = ggml_nbytes(input);
                    ggml_backend_tensor_set_async(split_backend, input_cpy, input->data, 0, copy_size);
                }

            } else
                // try async copy, but if not possible, we can still use a sync copy without synchronizing the dst backend, since we handle the synchronization here with multiple copies and events
                // TODO: add public function to facilitate this, since applications do not have direct access to the backend interface
                if (!split_backend->iface.cpy_tensor_async || !split_backend->iface.cpy_tensor_async(input_backend, split_backend, input, input_cpy)) {
                    ggml_backend_synchronize(input_backend);
                    if (needs_sync[split_backend_id]) {
                        if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                            ggml_backend_event_synchronize(sched->events[split_backend_id][sched->cur_copy]);
                        } else {
                            ggml_backend_synchronize(split_backend);
                        }
                        needs_sync[split_backend_id] = k_set_sync;
                    }
                    ggml_backend_tensor_copy(input, input_cpy);
                }
        }

    }
}

static ggml_status ggml_backend_sched_eval(ggml_backend_sched_t sched, ggml_backend_t split_backend, ggml_backend_sched_split * split) {
    if (!sched->callback_eval) {
#if IK_PRINT_TIMING
        int64_t tim2 = ggml_time_us();
        printf("%s(.1.): %d us\n", __func__, (int)(tim2-tim1));
#endif
        enum ggml_status ec = ggml_backend_graph_compute_async(split_backend, &split->graph);
        if (ec != GGML_STATUS_SUCCESS) {
            return ec;
        }
    } else {
        // similar to ggml_backend_compare_graph_backend
        for (int j0 = 0; j0 < split->graph.n_nodes; j0++) {
            struct ggml_tensor * t = split->graph.nodes[j0];

            // check if the user needs data from this node
            int need = sched->callback_eval(t, true, sched->callback_eval_user_data);

            int j1 = j0;

            // determine the range [j0, j1] of nodes that can be computed together
            while (!need && j1 < split->graph.n_nodes - 1) {
                t = split->graph.nodes[++j1];
                need = sched->callback_eval(t, true, sched->callback_eval_user_data);
            }

            struct ggml_cgraph gv = ggml_graph_view(&split->graph, j0, j1 + 1);

#if IK_PRINT_TIMING
            int64_t tim2 = ggml_time_us();
            printf("%s(.2.): %d us\n", __func__, (int)(tim2-tim1));
#endif

            enum ggml_status ec = ggml_backend_graph_compute_async(split_backend, &gv);
            if (ec != GGML_STATUS_SUCCESS) {
                return ec;
            }

            // TODO: pass backend to the callback, then the user can decide if they want to synchronize
            if (need == 1) {
                ggml_backend_synchronize(split_backend);
            }

            if (need && !sched->callback_eval(t, false, sched->callback_eval_user_data)) {
                break;
            }

            j0 = j1;
        }
    }
    return GGML_STATUS_SUCCESS;
}

static enum ggml_status ggml_backend_sched_compute_splits(ggml_backend_sched_t sched) {
    for (auto & item : sched->needs_sync) item = true;

    if (sched->is_async && sched->n_backends > 2 && sched->split_mode_graph && sched->has_reduce) {

        for (auto & s : sched->statuses) s = GGML_STATUS_SUCCESS;

        int first_reduce = -1;
        bool work_done = false;
#ifdef GGML_USE_OPENMP
        //This may not be available in old OpenMP versions
        //if (int nlevels = omp_get_max_active_levels(); nlevels < 2) {
        //    omp_set_max_active_levels(nlevels+1);
        //    //printf("%s: Setting omp max active levels to 2\n", __func__);
        //}
        bool has_cpu_work = false;
        for (int i = 0; i < sched->n_backends; ++i) {
            if (!sched->backend_splits[i].empty()) {
                auto split = sched->backend_splits[i].front();
                if (ggml_backend_is_cpu(sched->backends[split->backend_id])) {
                    //printf("CPU backend %d has %d splits\n", split->backend_id, (int)sched->backend_splits[i].size());
                    if (sched->backend_splits[i].size() > 1) {
                        has_cpu_work = true;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < sched->n_splits; i++) {
            auto split = &sched->splits[i];
            if (split->graph.n_nodes == 1 && split->graph.nodes[0]->op == GGML_OP_REDUCE) {
                first_reduce = split->backend_id;
                break;
            }
        }

        if (!has_cpu_work) {
        #pragma omp parallel num_threads(sched->n_backends)
        {

            int last_reduce = first_reduce;
            int ith = omp_get_thread_num();

            struct ggml_backend_sched_split * splits = sched->splits;

            std::vector<int32_t> ids;
            std::vector<uint32_t> unique_ids;
            ggml_tensor * last_ids_tensor = nullptr;

            for (int i = 0; i < sched->n_splits; i++) {
#if IK_PRINT_TIMING
                int64_t tim1 = ggml_time_us();
#endif
                struct ggml_backend_sched_split * split = &splits[i];
                int split_backend_id = split->backend_id;
                ggml_backend_t split_backend = sched->backends[split_backend_id];

                bool needs_barrier = split->n_inputs > 0 || split->graph.nodes[0]->op == GGML_OP_REDUCE;

                if (needs_barrier) {
                    #pragma omp barrier
                }

                if (split->n_inputs > 0) {
                    int copy_thread = last_reduce >= 0 ? last_reduce : 0;
                    if (ith == copy_thread) {
                        ggml_backend_sched_copy_inputs(sched, split, sched->needs_sync, ids, unique_ids, last_ids_tensor);
                    }
                    #pragma omp barrier
                }

                if (ith == split_backend_id) {

                    sched->statuses[ith] = ggml_backend_sched_eval(sched, split_backend, split);

                    if (split->n_inputs > 0 && !sched->own_cpy[split_backend_id]) {
                        sched->needs_sync[split_backend_id] = true;
                    } else {
                        for (int j = 0; j < split->n_inputs; ++j) {
                            if (ggml_backend_buffer_is_host(split->inputs[j]->buffer)) {
                                sched->needs_sync[split_backend_id] = true;
                            }
                        }
                    }
                }

                if (split->graph.nodes[0]->op == GGML_OP_REDUCE && i < sched->n_splits - 1) {
                    last_reduce = split_backend_id;
                    if (ith == split_backend_id) {
                        auto node = split->graph.nodes[0];
                        int n = node->op_params[1];
                        for (int j = 0; j < n; ++j) {
                            if (node->src[j]) {
                                sched->needs_sync[j] = false;
                            }
                        }
                    }
                    #pragma omp barrier
                }

                // record the event of this copy
                if (split->n_inputs > 0) {
                    if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                        ggml_backend_event_record(sched->events[split_backend_id][sched->cur_copy]);
                    }
                }
            }
        }
        work_done = true;
        }
#endif
        if (!work_done) {

        std::barrier barrier(sched->n_backends);
        auto compute = [sched, &barrier, first_reduce] (int ith) {

            struct ggml_backend_sched_split * splits = sched->splits;

            std::vector<int32_t> ids;
            std::vector<uint32_t> unique_ids;
            ggml_tensor * last_ids_tensor = nullptr;

            int last_reduce = first_reduce;

            for (int i = 0; i < sched->n_splits; i++) {
#if IK_PRINT_TIMING
                int64_t tim1 = ggml_time_us();
#endif
                struct ggml_backend_sched_split * split = &splits[i];
                int split_backend_id = split->backend_id;
                ggml_backend_t split_backend = sched->backends[split_backend_id];

                bool needs_barrier = split->n_inputs > 0 || split->graph.nodes[0]->op == GGML_OP_REDUCE;

                if (needs_barrier) {
                    barrier.arrive_and_wait();
                }

                if (split->n_inputs > 0) {
                    int copy_thread = last_reduce >= 0 ? last_reduce : 0;
                    if (ith == copy_thread) {
                        ggml_backend_sched_copy_inputs(sched, split, sched->needs_sync, ids, unique_ids, last_ids_tensor);
                    }
                    barrier.arrive_and_wait();
                }

                if (ith == split_backend_id) {

                    sched->statuses[ith] = ggml_backend_sched_eval(sched, split_backend, split);
                    if (split->n_inputs > 0 && !sched->own_cpy[split_backend_id]) {
                        sched->needs_sync[split_backend_id] = true;
                    } else {
                        for (int j = 0; j < split->n_inputs; ++j) {
                            if (ggml_backend_buffer_is_host(split->inputs[j]->buffer)) {
                                sched->needs_sync[split_backend_id] = true;
                            }
                        }
                    }
                }

                if (split->graph.nodes[0]->op == GGML_OP_REDUCE && i < sched->n_splits - 1) {
                    last_reduce = split_backend_id;
                    barrier.arrive_and_wait();
                    if (ith == split_backend_id) {
                        auto node = split->graph.nodes[0];
                        int n = node->op_params[1];
                        for (int j = 0; j < n; ++j) {
                            if (node->src[j]) {
                                sched->needs_sync[j] = false;
                            }
                        }
                    }
                }
                //if (needs_barrier) {
                //    barrier.arrive_and_wait();
                //}

                // record the event of this copy
                if (split->n_inputs > 0) {
                    if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                        printf("Recording event %d, %d\n", split_backend_id, sched->cur_copy);
                        ggml_backend_event_record(sched->events[split_backend_id][sched->cur_copy]);
                    }
                }
            }
        };

        for (int i = 0; i < sched->n_backends; ++i) sched->workers.emplace_back(compute, i);
        for (auto & w : sched->workers) w.join();
        sched->workers.clear();
        }
        for (auto status : sched->statuses) {
            if (status != GGML_STATUS_SUCCESS) return status;
        }
        return GGML_STATUS_SUCCESS;

    }

    struct ggml_backend_sched_split * splits = sched->splits;

    std::vector<int32_t> ids;
    std::vector<uint32_t> unique_ids;
    ggml_tensor * last_ids_tensor = nullptr;

    // MoE expert prefetch; pre-scan the splits for expert-weight matmuls whose
    // weights live in a host mmap. Two behaviors, both page-cache warmers.
    //  - lookahead streams the next splits' expert tensors in full while split
    //    i computes (batch/PP graphs only, where most experts are hit)
    //  - selective enqueues just the selected expert slices of a split's
    //    up/gate/down tensors once its ids have been copied to the host
    struct moe_split_info {
        int split;
        int64_t n_tokens;
        std::vector<ggml_tensor *> host_weights; // originals (host mmap)
        std::vector<ggml_tensor *> nodes;        // MoE nodes computed on a host buffer
    };
    std::vector<moe_split_info> moe_infos;
    const bool moe_prefetch = ggml_moe_prefetch_enabled();
    static const size_t moe_ahead = [] {
        const char * env = getenv("GGML_MOE_PREFETCH_AHEAD");
        return env ? (size_t) std::max(0, atoi(env)) : (size_t) 3;
    }();
    if (moe_prefetch) {
        ggml_moe_prefetch_new_epoch();
        for (int i = 0; i < sched->n_splits; i++) {
            moe_split_info info;
            info.split = i;
            info.n_tokens = 0;
            for (int n = 0; n < splits[i].graph.n_nodes; ++n) {
                ggml_tensor * node = splits[i].graph.nodes[n];
                if (node->op != GGML_OP_MUL_MAT_ID && node->op != GGML_OP_MOE_FUSED_UP_GATE) {
                    continue;
                }
                ggml_tensor * node_ids = node->op == GGML_OP_MUL_MAT_ID ? node->src[2] : node->src[3];
                info.n_tokens = std::max(info.n_tokens, node_ids ? node_ids->ne[1] : 0);
                ggml_tensor * ws[2] = { node->src[0], node->op == GGML_OP_MOE_FUSED_UP_GATE ? node->src[1] : nullptr };
                bool node_on_host = false;
                for (ggml_tensor * w : ws) {
                    if (w && w->buffer && ggml_backend_buffer_is_host(w->buffer) &&
                            ggml_backend_buffer_get_usage(w->buffer) == GGML_BACKEND_BUFFER_USAGE_WEIGHTS) {
                        info.host_weights.push_back(w);
                        node_on_host = true;
                    }
                }
                if (node_on_host) {
                    info.nodes.push_back(node);
                }
            }
            // in the offloaded case the node's weight srcs were rewritten to
            // device copies; the host originals arrive as split inputs
            for (int j = 0; j < splits[i].n_inputs; ++j) {
                ggml_tensor * input = splits[i].inputs[j];
                if (input->ne[2] > 1 && input->buffer && ggml_backend_buffer_is_host(input->buffer) &&
                        ggml_backend_buffer_get_usage(input->buffer) == GGML_BACKEND_BUFFER_USAGE_WEIGHTS) {
                    info.host_weights.push_back(input);
                }
            }
            if (!info.host_weights.empty()) {
                moe_infos.push_back(std::move(info));
            }
        }
    }
    size_t moe_next  = 0; // first moe_infos entry with split >= current split
    size_t moe_enq   = 0; // moe_infos entries already enqueued for lookahead

    for (int i = 0; i < sched->n_splits; i++) {
#if IK_PRINT_TIMING
        int64_t tim1 = ggml_time_us();
#endif
        struct ggml_backend_sched_split * split = &splits[i];
        int split_backend_id = split->backend_id;
        ggml_backend_t split_backend = sched->backends[split_backend_id];

        if (moe_prefetch && !moe_infos.empty()) {
            while (moe_next < moe_infos.size() && moe_infos[moe_next].split < i) {
                moe_next++;
            }
            // keep the next `moe_ahead` MoE-bearing splits streaming in
            const size_t want_end = std::min(moe_next + moe_ahead, moe_infos.size());
            for (size_t k = std::max(moe_enq, moe_next); k < want_end; ++k) {
                if (moe_infos[k].n_tokens >= 32) { // batch graphs touch most experts (min batch offload)
                    for (ggml_tensor * w : moe_infos[k].host_weights) {
                        ggml_moe_prefetch_tensor(w);
                    }
                }
                moe_enq = k + 1;
            }
        }

        // copy the input tensors to the split backend
        ggml_backend_sched_copy_inputs(sched, split, sched->needs_sync, ids, unique_ids, last_ids_tensor);

        // ids are now final and host-visible; enqueue the selected expert
        // slices of this split's host-computed MoE matmuls (up/gate and down
        // share one ids tensor, so the down weights stream in during up/gate)
        if (moe_prefetch && moe_next < moe_infos.size() && moe_infos[moe_next].split == i) {
            for (ggml_tensor * node : moe_infos[moe_next].nodes) {
                ggml_moe_prefetch_node(node);
            }
        }

        if (split->n_inputs > 0 && !sched->own_cpy[split_backend_id]) {
            sched->needs_sync[split_backend_id] = true;
        } else {
            for (int j = 0; j < split->n_inputs; ++j) {
                if (ggml_backend_buffer_is_host(split->inputs[j]->buffer)) {
                    sched->needs_sync[split_backend_id] = true;
                }
            }
        }
        auto ec = ggml_backend_sched_eval(sched, split_backend, split);
        if (ec != GGML_STATUS_SUCCESS) {
            return ec;
        }

        // the pages the lookahead streamer just read for this split are one-shot
        // streaming traffic; MADV_COLD them so the decode working set survives
        if (moe_prefetch && moe_next < moe_infos.size() && moe_infos[moe_next].split == i &&
                moe_infos[moe_next].n_tokens >= 32) {
            for (ggml_tensor * w : moe_infos[moe_next].host_weights) {
                ggml_moe_prefetch_cold(w);
            }
        }

        // record the event of this copy
        if (split->n_inputs > 0) {
            if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                ggml_backend_event_record(sched->events[split_backend_id][sched->cur_copy]);
            }
        }
    }

    sched->cur_copy = (sched->cur_copy + 1) % sched->n_copies;

    return GGML_STATUS_SUCCESS;
}

static enum ggml_status ggml_backend_sched_compute_splits_turboprefill(ggml_backend_sched_t sched, int turboprefill_stage) {

    GGML_ASSERT(sched);
    struct ggml_backend_sched_split * splits = sched->splits;

    ggml_tensor * prev_ids_tensor = nullptr;
    std::vector<int32_t> ids;
    std::vector<ggml_bitset_t> used_ids;
    std::vector<int32_t> standard_capture_ids;
    std::vector<uint32_t> standard_capture_unique_ids;
    ggml_tensor * standard_capture_last_ids_tensor = nullptr;

    auto run_split_range = [&](int split_begin, int split_end, int split_step) -> enum ggml_status {

        for (int split_id = split_begin; split_id != split_end; split_id += split_step) {
        struct ggml_backend_sched_split * split = &splits[split_id];
        int split_backend_id = split->backend_id;
        ggml_backend_t split_backend = sched->backends[split_backend_id];
        for (int input_id = 0; input_id < split->n_inputs; input_id++) {
            ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, split->inputs[input_id]);
            struct ggml_tensor * input = split->inputs[input_id];
            struct ggml_tensor * input_cpy = tensor_copy(input, split_backend_id, sched->cur_copy);
            if (input->flags & GGML_TENSOR_FLAG_INPUT) {
                if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                    ggml_backend_event_synchronize(sched->events[split_backend_id][sched->cur_copy]);
                } else {
                    ggml_backend_synchronize(split_backend);
                }
                ggml_backend_tensor_copy(input, input_cpy);
            } else {
                if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                    ggml_backend_event_wait(split_backend, sched->events[split_backend_id][sched->cur_copy]);
                } else {
                    ggml_backend_synchronize(split_backend);
                }

                ggml_tensor * node = split->graph.nodes[0];
                if (split->graph.n_nodes > 0 &&
                    ggml_backend_buffer_get_usage(input->buffer) == GGML_BACKEND_BUFFER_USAGE_WEIGHTS &&
                    ggml_backend_buffer_is_host(input->buffer) && (
                    (node->src[0] == input_cpy && node->op == GGML_OP_MUL_MAT_ID)
                    )) {

                    const int64_t n_expert   = node->op == GGML_OP_MUL_MAT_ID ? input->ne[2] : input->ne[1];
                    const size_t expert_size = node->op == GGML_OP_MUL_MAT_ID ? input->nb[2] : input->nb[1];

                    ggml_backend_synchronize(input_backend);

                    ggml_tensor * ids_tensor = node->src[2];
                    ggml_backend_t ids_backend = split_backend;

                    for (int i = input_id + 1; i < split->n_inputs; i++) {
                        if (ids_tensor == tensor_copy(split->inputs[i], split_backend_id, sched->cur_copy)) {
                            ids_tensor = split->inputs[i];
                            ids_backend = ggml_backend_sched_get_tensor_backend(sched, split->inputs[i]);
                            break;
                        }
                    }

                    if (ids_tensor != prev_ids_tensor) {
                        ids.resize(ggml_nbytes(ids_tensor) / sizeof(int32_t));
                        ggml_backend_tensor_get_async(ids_backend, ids_tensor, ids.data(), 0, ggml_nbytes(ids_tensor));
                        ggml_backend_synchronize(ids_backend);

                        used_ids.clear();
                        used_ids.resize(ggml_bitset_size(n_expert));
                        for (int64_t i1 = 0; i1 < ids_tensor->ne[1]; i1++) {
                            for (int64_t i0 = 0; i0 < ids_tensor->ne[0]; i0++) {
                                int32_t id = ids[i1 * ids_tensor->nb[1]/sizeof(int32_t) + i0 * ids_tensor->nb[0]/sizeof(int32_t)];
                                GGML_ASSERT(id >= 0 && id < n_expert);
                                ggml_bitset_set(used_ids.data(), id);
                            }
                        }

                        prev_ids_tensor = ids_tensor;
                    }

                    auto copy_experts = [&](int32_t first_id, int32_t last_id) {
                        const size_t expert_offset = first_id * expert_size;
                        const size_t expert_size_copy =  (last_id - first_id + 1) * expert_size;
                        const size_t padding = std::min<size_t>(expert_size, 512);
                        const size_t padding_end = last_id < n_expert - 1 ? padding : 0;

                        ggml_backend_tensor_set_async(split_backend,
                            input_cpy,
                            (const uint8_t *)input->data + expert_offset, expert_offset,
                            expert_size_copy + padding_end);
                    };

                    int id = 0;
                    while (!ggml_bitset_get(used_ids.data(), id)) {
                        id++;
                    }
                    int32_t first_id = id;
                    int32_t last_id = first_id;

                    for (++id; id < n_expert; ++id) {
                        if (!ggml_bitset_get(used_ids.data(), id)) {
                            continue;
                        }

                        if (id == last_id + 1) {
                            last_id = id;
                            continue;
                        }

                        copy_experts(first_id, last_id);

                        first_id = id;
                        last_id = id;
                    }
                    copy_experts(first_id, last_id);
                } else {
                    if (!split_backend->iface.cpy_tensor_async || !split_backend->iface.cpy_tensor_async(input_backend, split_backend, input, input_cpy)) {
                        ggml_backend_synchronize(input_backend);
                        if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                            ggml_backend_event_synchronize(sched->events[split_backend_id][sched->cur_copy]);
                        } else {
                            ggml_backend_synchronize(split_backend);
                        }
                        ggml_backend_tensor_copy(input, input_cpy);
                    }
                }
            }

        }

        if (!sched->callback_eval) {
            enum ggml_status ec = ggml_backend_graph_compute_async(split_backend, &split->graph);
            if (ec != GGML_STATUS_SUCCESS) {
                return ec;
            }
        } else {
            for (int j0 = 0; j0 < split->graph.n_nodes; j0++) {
                struct ggml_tensor * t = split->graph.nodes[j0];

                bool need = sched->callback_eval(t, true, sched->callback_eval_user_data);

                int j1 = j0;

                while (!need && j1 < split->graph.n_nodes - 1) {
                    t = split->graph.nodes[++j1];
                    need = sched->callback_eval(t, true, sched->callback_eval_user_data);
                }

                struct ggml_cgraph gv = ggml_graph_view(&split->graph, j0, j1 + 1);

                enum ggml_status ec = ggml_backend_graph_compute_async(split_backend, &gv);
                if (ec != GGML_STATUS_SUCCESS) {
                    return ec;
                }

                ggml_backend_synchronize(split_backend);

                if (need && !sched->callback_eval(t, false, sched->callback_eval_user_data)) {
                    break;
                }

                j0 = j1;
            }
        }

        if (split->n_inputs > 0) {
            if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                ggml_backend_event_record(sched->events[split_backend_id][sched->cur_copy]);
            }
            }
        }

        return GGML_STATUS_SUCCESS;
    };
    auto run_standard_split0_capture = [&]() -> enum ggml_status {
        if (sched->n_splits < 1) {
            return GGML_STATUS_SUCCESS;
        }

        for (auto & item : sched->needs_sync) {
            item = true;
        }
        standard_capture_ids.clear();
        standard_capture_unique_ids.clear();
        standard_capture_last_ids_tensor = nullptr;

        struct ggml_backend_sched_split * split = &splits[0];
        const int split_backend_id = split->backend_id;
        ggml_backend_t split_backend = sched->backends[split_backend_id];

        ggml_backend_sched_copy_inputs(
                sched, split, sched->needs_sync,
                standard_capture_ids, standard_capture_unique_ids,
                standard_capture_last_ids_tensor);

        if (split->n_inputs > 0 && !sched->own_cpy[split_backend_id]) {
            sched->needs_sync[split_backend_id] = true;
        } else {
            for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
                if (ggml_backend_buffer_is_host(split->inputs[input_id]->buffer)) {
                    sched->needs_sync[split_backend_id] = true;
                }
            }
        }

        enum ggml_status status = ggml_backend_sched_eval(sched, split_backend, split);
        if (status != GGML_STATUS_SUCCESS) {
            return status;
        }

        if (split->n_inputs > 0 && sched->events[split_backend_id][sched->cur_copy] != nullptr) {
            ggml_backend_event_record(sched->events[split_backend_id][sched->cur_copy]);
        }
        return GGML_STATUS_SUCCESS;
    };
    auto prepare_standard_split1_inputs_capture = [&]() -> enum ggml_status {
        if (sched->n_splits < 2) {
            return GGML_STATUS_SUCCESS;
        }

        struct ggml_backend_sched_split * split = &splits[1];
        ggml_backend_sched_copy_inputs(
                sched, split, sched->needs_sync,
                standard_capture_ids, standard_capture_unique_ids,
                standard_capture_last_ids_tensor);
        return GGML_STATUS_SUCCESS;
    };
    auto capture_tensor_meta_recursive = [&](auto && self,
            std::vector<ggml_backend_sched_tp_tensor_meta> & metas,
            struct ggml_tensor * tensor) -> void {
        if (tensor == nullptr) {
            return;
        }

        for (const auto & meta : metas) {
            if (meta.tensor == tensor) {
                return;
            }
        }

        ggml_backend_sched_tp_capture_tensor_meta(metas, tensor);
        if (tensor->view_src != nullptr) {
            self(self, metas, tensor->view_src);
        }
        for (int src_id = 0; src_id < GGML_MAX_SRC; ++src_id) {
            if (tensor->src[src_id] != nullptr) {
                self(self, metas, tensor->src[src_id]);
            }
        }
    };

    auto capture_tensor_tree_meta = [&](std::vector<ggml_backend_sched_tp_tensor_meta> & metas) {
        for (int split_id = 0; split_id < sched->n_splits; ++split_id) {
            struct ggml_backend_sched_split * split = &splits[split_id];
            const int split_backend_id = split->backend_id;

            for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
                struct ggml_tensor * input = split->inputs[input_id];
                capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, input);
                for (int copy_id = 0; copy_id < sched->n_copies; ++copy_id) {
                    capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, tensor_copy(input, split_backend_id, copy_id));
                }
            }

            for (int node_id = 0; node_id < split->graph.n_nodes; ++node_id) {
                capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, split->graph.nodes[node_id]);
            }
            for (int leaf_id = 0; leaf_id < split->graph.n_leafs; ++leaf_id) {
                capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, split->graph.leafs[leaf_id]);
            }
        }

        for (int node_id = 0; node_id < sched->graph.n_nodes; ++node_id) {
            capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, sched->graph.nodes[node_id]);
        }
        for (int leaf_id = 0; leaf_id < sched->graph.n_leafs; ++leaf_id) {
            capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, sched->graph.leafs[leaf_id]);
        }
    };

    auto capture_tensor_tree_meta_for_split = [&](std::vector<ggml_backend_sched_tp_tensor_meta> & metas, int split_id) {
        if (split_id < 0 || split_id >= sched->n_splits) {
            return;
        }

        struct ggml_backend_sched_split * split = &splits[split_id];
        const int split_backend_id = split->backend_id;

        for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
            struct ggml_tensor * input = split->inputs[input_id];
            capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, input);
            for (int copy_id = 0; copy_id < sched->n_copies; ++copy_id) {
                capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, tensor_copy(input, split_backend_id, copy_id));
            }
        }

        for (int node_id = 0; node_id < split->graph.n_nodes; ++node_id) {
            capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, split->graph.nodes[node_id]);
        }
        for (int leaf_id = 0; leaf_id < split->graph.n_leafs; ++leaf_id) {
            capture_tensor_meta_recursive(capture_tensor_meta_recursive, metas, split->graph.leafs[leaf_id]);
        }
    };

    auto find_saved_split_tensor_meta = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            const struct ggml_tensor * tensor) -> const ggml_backend_sched_tp_tensor_meta * {
        if (tensor == nullptr) {
            return nullptr;
        }

        if (split_id < 0 || split_id >= (int) saved.split_metas.size()) {
            return nullptr;
        }

        const auto & metas = saved.split_metas[split_id];
        if (split_id < (int) saved.split_meta_index.size()) {
            const auto & index = saved.split_meta_index[split_id];
            auto it = index.find(tensor);
            if (it != index.end() && it->second < metas.size()) {
                return &metas[it->second];
            }
        }

        for (const auto & meta : metas) {
            if (meta.tensor == tensor) {
                return &meta;
            }
        }
        return nullptr;
    };
    auto apply_saved_tensor_meta_shape_only_one = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            struct ggml_tensor * tensor) -> const ggml_backend_sched_tp_tensor_meta * {
        const auto * meta = find_saved_split_tensor_meta(saved, split_id, tensor);
        if (meta == nullptr || tensor == nullptr) {
            return nullptr;
        }

        tensor->type  = meta->type;
        tensor->flags = meta->flags;

        for (int i = 0; i < GGML_MAX_DIMS; ++i) {
            tensor->ne[i] = meta->ne[i];
            tensor->nb[i] = meta->nb[i];
        }

        return meta;
    };
    auto apply_saved_tensor_meta_full_one = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            struct ggml_tensor * tensor) -> const ggml_backend_sched_tp_tensor_meta * {
        const auto * meta = apply_saved_tensor_meta_shape_only_one(saved, split_id, tensor);
        if (meta == nullptr || tensor == nullptr) {
            return nullptr;
        }

        tensor->data      = meta->data;
        tensor->buffer    = meta->buffer;
        tensor->view_src  = meta->view_src;
        tensor->view_offs = meta->view_offs;

        return meta;
    };
    auto apply_saved_split_tensor_metas = [&](const ggml_backend_sched_tp_saved_ub & saved, int split_id) -> bool {
        if (split_id < 0 || split_id >= (int) saved.split_metas.size()) {
            return false;
        }

        // A delayed UB must see the complete tensor descriptors captured for
        // that UB.  Applying only shapes leaves dynamic views pointing at the
        // descriptors of a later UB.
        for (const auto & meta : saved.split_metas[split_id]) {
            if (meta.tensor == nullptr ||
                apply_saved_tensor_meta_full_one(saved, split_id, meta.tensor) == nullptr) {
                return false;
            }
        }

        return true;
    };
    auto tp_tensor_runtime_buffer = [&](const struct ggml_tensor * tensor) -> ggml_backend_buffer_t {
        if (tensor == nullptr) {
            return nullptr;
        }
        return tensor->view_src ? tensor->view_src->buffer : tensor->buffer;
    };
    auto tp_tensor_is_weight = [&](const struct ggml_tensor * tensor) -> bool {
        ggml_backend_buffer_t buf = tp_tensor_runtime_buffer(tensor);
        return buf != nullptr && ggml_backend_buffer_get_usage(buf) == GGML_BACKEND_BUFFER_USAGE_WEIGHTS;
    };
    auto tp_tensor_has_external_input_root = [&](
            const struct ggml_tensor * tensor) -> bool {
        for (const struct ggml_tensor * cur = tensor; cur != nullptr; cur = cur->view_src) {
            if ((cur->flags & GGML_TENSOR_FLAG_INPUT) && !tp_tensor_is_weight(cur)) {
                return true;
            }
        }
        return false;
    };
    auto tp_is_scheduler_input_copy = [&](const struct ggml_tensor * tensor) -> bool {
        if (tensor == nullptr) {
            return false;
        }

        for (int split_id = 0; split_id < sched->n_splits; ++split_id) {
            const struct ggml_backend_sched_split * split = &splits[split_id];
            for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
                struct ggml_tensor * input = split->inputs[input_id];
                if (input == nullptr || input == tensor) {
                    continue;
                }
                for (int backend_id = 0; backend_id < sched->n_backends; ++backend_id) {
                    for (int copy_id = 0; copy_id < sched->n_copies; ++copy_id) {
                        if (tensor_copy(input, backend_id, copy_id) == tensor) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    };
    auto tp_find_input_producer_split = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            const struct ggml_tensor * tensor,
            int split_id) -> int {
        if (tensor == nullptr) {
            return -1;
        }
        for (int prev_split_id = split_id - 1; prev_split_id >= 0; --prev_split_id) {
            const auto & snap = saved.split_graphs[prev_split_id];
            for (const auto * node : snap.nodes) {
                if (node == tensor ||
                    (tensor->view_src != nullptr && node == tensor->view_src) ||
                    (node != nullptr && node->view_src != nullptr && node->view_src == tensor)) {
                    return prev_split_id;
                }
            }
        }
        return -1;
    };
    auto capture_turboprefill_ub = [&](int ub_id) -> ggml_backend_sched_tp_saved_ub {
        ggml_backend_sched_tp_saved_ub saved;
        saved.turboprefill = ub_id > 0 ? ub_id : -ub_id;
        saved.prepared_input_banks.resize(sched->n_splits);
        saved.info_banks.resize(sched->n_splits);
        saved.live_input_banks.resize(sched->n_splits);
        saved.intermediate_banks.resize(sched->n_splits);
        saved.input_plans.resize(sched->n_splits);
        saved.split_graphs.resize(sched->n_splits);
        saved.split_metas.resize(sched->n_splits);
        saved.split_meta_index.resize(sched->n_splits);

        for (int meta_split_id = 0; meta_split_id < sched->n_splits; ++meta_split_id) {
            capture_tensor_tree_meta_for_split(saved.split_metas[meta_split_id], meta_split_id);
            auto & index = saved.split_meta_index[meta_split_id];
            const auto & metas = saved.split_metas[meta_split_id];
            index.reserve(metas.size());
            for (size_t meta_id = 0; meta_id < metas.size(); ++meta_id) {
                if (metas[meta_id].tensor != nullptr) {
                    index[metas[meta_id].tensor] = meta_id;
                }
            }
        }

        for (int snap_split_id = 0; snap_split_id < sched->n_splits; ++snap_split_id) {
            const struct ggml_backend_sched_split * snap_split = &splits[snap_split_id];
            auto & snap = saved.split_graphs[snap_split_id];
            snap.split = *snap_split;
            snap.backend_id = snap_split->backend_id;
            snap.inputs.reserve(snap_split->n_inputs);
            for (int input_id = 0; input_id < snap_split->n_inputs; ++input_id) {
                struct ggml_tensor * input = snap_split->inputs[input_id];
                snap.inputs.push_back(input);
            }
            snap.nodes.reserve(snap_split->graph.n_nodes);
            snap.node_srcs.reserve(snap_split->graph.n_nodes);
            for (int node_id = 0; node_id < snap_split->graph.n_nodes; ++node_id) {
                struct ggml_tensor * node = snap_split->graph.nodes[node_id];
                snap.nodes.push_back(node);
                ggml_backend_sched_tp_node_srcs srcs = {};
                srcs.node = node;
                for (int src_id = 0; src_id < GGML_MAX_SRC; ++src_id) {
                    srcs.src[src_id] = node != nullptr ? node->src[src_id] : nullptr;
                }
                snap.node_srcs.push_back(srcs);
            }
            snap.leafs.reserve(snap_split->graph.n_leafs);
            for (int leaf_id = 0; leaf_id < snap_split->graph.n_leafs; ++leaf_id) {
                snap.leafs.push_back(snap_split->graph.leafs[leaf_id]);
            }
        }

        for (int plan_split_id = 0; plan_split_id < sched->n_splits; ++plan_split_id) {
            const struct ggml_backend_sched_split * plan_split = &splits[plan_split_id];
            auto & plans = saved.input_plans[plan_split_id];
            plans.resize(plan_split->n_inputs);

            for (int input_id = 0; input_id < plan_split->n_inputs; ++input_id) {
                struct ggml_tensor * input = plan_split->inputs[input_id];
                auto & plan = plans[input_id];
                plan.key = input;
                plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UNKNOWN;
                plan.producer_split_id = -1;

                if (input == nullptr) {
                    continue;
                }

                const bool is_weight = tp_tensor_is_weight(input);
                const bool is_external = !is_weight &&
                        tp_tensor_has_external_input_root(input);

                if (plan_split_id == 0 && !is_weight) {
                    plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT;
                    continue;
                }
                if (is_weight) {
                    plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_LIVE_WEIGHT;
                    continue;
                }

                // Split 0 has just been executed through the standard input
                // preparation and evaluation path.  For split 1, retain the
                // exact input-copy bytes produced by that path rather than
                // reconstructing their source during the delayed replay.
                if (plan_split_id == 1) {
                    plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_PREPARED_INPUT;
                    continue;
                }

                if (plan_split_id > 0 && is_external) {
                    plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT;
                    continue;
                }

                const int producer_split_id = tp_find_input_producer_split(saved, input, plan_split_id);
                if (producer_split_id >= 0) {
                    if (producer_split_id == 0) {
                        plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT;
                        plan.producer_split_id = producer_split_id;
                        continue;
                    }
                    plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_INTERMEDIATE;
                    plan.producer_split_id = producer_split_id;
                    saved.intermediate_banks[plan_split_id].push_back({ input, {} });
                    continue;
                }

                plan.source_kind = GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_LIVE_INPUT;
            }
        }

        if (sched->n_splits > 0 && splits[0].n_inputs > 0) {
            saved.split0_inputs.reserve(splits[0].n_inputs);
            for (int input_id = 0; input_id < splits[0].n_inputs; ++input_id) {
                struct ggml_tensor * input = splits[0].inputs[input_id];
                saved.split0_inputs.push_back({ input, {} });
                auto & entry = saved.split0_inputs.back();

                if (input == nullptr) {
                    continue;
                }

                if (tp_tensor_is_weight(input)) {
                    continue;
                }

                ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
                const int input_backend_id = ggml_backend_sched_backend_id(sched, input_backend);
                ggml_backend_event_t input_event =
                        input_backend_id >= 0 ? sched->events[input_backend_id][sched->cur_copy] : nullptr;
                const size_t nbytes = ggml_nbytes(input);
                entry.data.resize(nbytes);
                ggml_backend_sched_tp_tensor_get_to_ram(input_backend, input_event, input, entry.data.data(), nbytes);

            }
        }

        for (int info_split_id = 0; info_split_id < sched->n_splits; ++info_split_id) {
            struct ggml_backend_sched_split * info_split = &splits[info_split_id];

            for (int input_id = 0; input_id < info_split->n_inputs; ++input_id) {
                struct ggml_tensor * input = info_split->inputs[input_id];
                if (input == nullptr) {
                    continue;
                }

                if (info_split_id >= (int) saved.input_plans.size() ||
                    input_id >= (int) saved.input_plans[info_split_id].size()) {
                    continue;
                }
                const auto & plan = saved.input_plans[info_split_id][input_id];
                if (plan.source_kind != GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT) {
                    continue;
                }

                ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
                const int input_backend_id = ggml_backend_sched_backend_id(sched, input_backend);
                ggml_backend_event_t input_event =
                        input_backend_id >= 0 ? sched->events[input_backend_id][sched->cur_copy] : nullptr;
                const size_t nbytes = ggml_nbytes(input);
                saved.info_banks[info_split_id].push_back({ input, {} });
                auto & entry = saved.info_banks[info_split_id].back();
                entry.data.resize(nbytes);
                ggml_backend_sched_tp_tensor_get_to_ram(input_backend, input_event, input, entry.data.data(), nbytes);
            }
        }

        // The caller has prepared split 1 with ggml_backend_sched_copy_inputs
        // immediately after standard split 0.  Save the resulting destination
        // copies, because these are the exact bytes read by split 1's graph.
        if (sched->n_splits > 1) {
            const int prepared_split_id = 1;
            struct ggml_backend_sched_split * prepared_split = &splits[prepared_split_id];
            ggml_backend_t prepared_backend = sched->backends[prepared_split->backend_id];
            auto & bank = saved.prepared_input_banks[prepared_split_id];
            bank.reserve(prepared_split->n_inputs);

            for (int input_id = 0; input_id < prepared_split->n_inputs; ++input_id) {
                const auto & plan = saved.input_plans[prepared_split_id][input_id];
                if (plan.source_kind != GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_PREPARED_INPUT) {
                    continue;
                }

                struct ggml_tensor * input = prepared_split->inputs[input_id];
                struct ggml_tensor * input_cpy =
                        input != nullptr ? tensor_copy(input, prepared_split->backend_id, sched->cur_copy) : nullptr;
                if (input == nullptr || input_cpy == nullptr) {
                    continue;
                }

                bank.push_back({ input, {} });
                auto & entry = bank.back();
                const size_t nbytes = ggml_nbytes(input_cpy);
                entry.data.resize(nbytes);
                ggml_backend_sched_tp_tensor_get_to_ram(
                        prepared_backend, nullptr, input_cpy, entry.data.data(), nbytes);
            }
        }

        for (int live_split_id = 0; live_split_id < sched->n_splits; ++live_split_id) {
            struct ggml_backend_sched_split * live_split = &splits[live_split_id];

            for (int input_id = 0; input_id < live_split->n_inputs; ++input_id) {
                struct ggml_tensor * input = live_split->inputs[input_id];
                if (input == nullptr) {
                    continue;
                }

                if (live_split_id >= (int) saved.input_plans.size() ||
                    input_id >= (int) saved.input_plans[live_split_id].size()) {
                    continue;
                }
                const auto & plan = saved.input_plans[live_split_id][input_id];
                if (plan.source_kind != GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_LIVE_INPUT) {
                    continue;
                }

                ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
                const int input_backend_id = ggml_backend_sched_backend_id(sched, input_backend);
                ggml_backend_event_t input_event =
                        input_backend_id >= 0 ? sched->events[input_backend_id][sched->cur_copy] : nullptr;
                const size_t nbytes = ggml_nbytes(input);
                saved.live_input_banks[live_split_id].push_back({ input, {} });
                auto & entry = saved.live_input_banks[live_split_id].back();
                entry.data.resize(nbytes);
                ggml_backend_sched_tp_tensor_get_to_ram(input_backend, input_event, input, entry.data.data(), nbytes);
            }
        }

        // Capture every non-weight root input reachable from each split graph.
        // Unlike info_banks, this includes inputs that the scheduler did not
        // expose through split->inputs (for example, KV index tensors).
        for (int graph_split_id = 0; graph_split_id < sched->n_splits; ++graph_split_id) {
            const auto & metas = saved.split_metas[graph_split_id];
            for (const auto & meta : metas) {
                const struct ggml_tensor * input = meta.tensor;
                if (input == nullptr ||
                    !(input->flags & GGML_TENSOR_FLAG_INPUT) ||
                    tp_tensor_is_weight(input) ||
                    tp_is_scheduler_input_copy(input) ||
                    tp_tensor_runtime_buffer(input) == nullptr) {
                    continue;
                }

                ggml_backend_sched_tp_graph_input_entry * entry = nullptr;
                for (auto & candidate : saved.graph_inputs) {
                    if (candidate.key == input) {
                        entry = &candidate;
                        break;
                    }
                }

                if (entry == nullptr) {
                    ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(
                            sched, const_cast<struct ggml_tensor *>(input));
                    if (input_backend == nullptr) {
                        continue;
                    }

                    saved.graph_inputs.push_back({ input, {}, {} });
                    entry = &saved.graph_inputs.back();

                    const int input_backend_id = ggml_backend_sched_backend_id(sched, input_backend);
                    ggml_backend_event_t input_event =
                            input_backend_id >= 0 ? sched->events[input_backend_id][sched->cur_copy] : nullptr;
                    const size_t nbytes = ggml_nbytes(input);
                    entry->data.resize(nbytes);
                    ggml_backend_sched_tp_tensor_get_to_ram(
                            input_backend, input_event, input, entry->data.data(), nbytes);
                }

                bool used_by_split = false;
                for (const int saved_split_id : entry->split_ids) {
                    if (saved_split_id == graph_split_id) {
                        used_by_split = true;
                        break;
                    }
                }
                if (!used_by_split) {
                    entry->split_ids.push_back(graph_split_id);
                }
            }
        }

        return saved;
    };

    auto load_saved_info_entry = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            const struct ggml_tensor * key,
            ggml_backend_t dst_backend,
            struct ggml_tensor * dst) -> bool {
        if (split_id >= (int) saved.info_banks.size()) {
            return false;
        }

        const auto & bank = saved.info_banks[split_id];
        const ggml_backend_sched_tp_info_entry * entry = nullptr;
        for (const auto & candidate : bank) {
            if (candidate.key == key) {
                entry = &candidate;
                break;
            }
        }

        if (entry == nullptr) {
            return false;
        }

        const size_t nbytes = ggml_nbytes(dst);
        if (entry->data.size() < nbytes) {
            return false;
        }

        ggml_backend_sched_tp_tensor_set_from_ram(dst_backend, dst, entry->data.data(), nbytes);
        return true;
    };
    auto load_saved_prepared_input_entry = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            const struct ggml_tensor * key,
            ggml_backend_t dst_backend,
            struct ggml_tensor * dst) -> bool {
        if (split_id < 0 || split_id >= (int) saved.prepared_input_banks.size()) {
            return false;
        }

        const auto & bank = saved.prepared_input_banks[split_id];
        const ggml_backend_sched_tp_info_entry * entry = nullptr;
        for (const auto & candidate : bank) {
            if (candidate.key == key) {
                entry = &candidate;
                break;
            }
        }
        if (entry == nullptr) {
            return false;
        }

        const size_t nbytes = ggml_nbytes(dst);
        if (entry->data.size() < nbytes) {
            return false;
        }

        ggml_backend_sched_tp_tensor_set_from_ram(dst_backend, dst, entry->data.data(), nbytes);
        return true;
    };
    auto load_saved_intermediate_entry = [&]( 
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            const struct ggml_tensor * key,
            ggml_backend_t dst_backend,
            struct ggml_tensor * dst) -> bool {
        if (split_id >= (int) saved.intermediate_banks.size()) {
            return false;
        }

        const auto & bank = saved.intermediate_banks[split_id];
        const ggml_backend_sched_tp_info_entry * entry = nullptr;
        for (const auto & candidate : bank) {
            if (candidate.key == key) {
                entry = &candidate;
                break;
            }
        }
        if (entry == nullptr) {
            return false;
        }

        const size_t nbytes = ggml_nbytes(dst);
        if (entry->data.size() < nbytes) {
            return false;
        }

        ggml_backend_sched_tp_tensor_set_from_ram(dst_backend, dst, entry->data.data(), nbytes);
        return true;
    };
    auto restore_saved_live_input_entry = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            struct ggml_tensor * input) -> bool {
        if (input == nullptr) {
            return false;
        }
        if (split_id >= (int) saved.live_input_banks.size()) {
            return false;
        }

        const auto & bank = saved.live_input_banks[split_id];
        const ggml_backend_sched_tp_info_entry * entry = nullptr;
        for (const auto & candidate : bank) {
            if (candidate.key == input) {
                entry = &candidate;
                break;
            }
        }
        if (entry == nullptr) {
            return false;
        }

        ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
        if (input_backend == nullptr) {
            return false;
        }

        const size_t nbytes = ggml_nbytes(input);
        if (entry->data.size() < nbytes) {
            return false;
        }

        ggml_backend_sched_tp_tensor_set_from_ram(input_backend, input, entry->data.data(), nbytes);
        ggml_backend_synchronize(input_backend);
        return true;
    };
    auto saved_input_plan = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id,
            int input_id) -> const ggml_backend_sched_tp_input_plan * {
        if (split_id < 0 || split_id >= (int) saved.input_plans.size()) {
            return nullptr;
        }
        const auto & plans = saved.input_plans[split_id];
        if (input_id < 0 || input_id >= (int) plans.size()) {
            return nullptr;
        }
        return &plans[input_id];
    };
    auto copy_live_tensor_like_standard = [&](
            int split_backend_id,
            ggml_backend_t split_backend,
            struct ggml_tensor * input,
            struct ggml_tensor * input_cpy) -> bool {
        if (input == nullptr || input_cpy == nullptr) {
            return false;
        }
        if (input == input_cpy) {
            return true;
        }

        ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
        if (input_backend == nullptr) {
            return false;
        }

        if (!split_backend->iface.cpy_tensor_async ||
            !split_backend->iface.cpy_tensor_async(input_backend, split_backend, input, input_cpy)) {
            ggml_backend_synchronize(input_backend);
            if (sched->events[split_backend_id][sched->cur_copy] != NULL) {
                ggml_backend_event_synchronize(sched->events[split_backend_id][sched->cur_copy]);
            } else {
                ggml_backend_synchronize(split_backend);
            }
            ggml_backend_tensor_copy(input, input_cpy);
        }
        return true;
    };

    auto load_saved_split0_input = [&](
            const ggml_backend_sched_tp_saved_ub & saved,
            int input_id,
            ggml_backend_t dst_backend,
            struct ggml_tensor * dst) -> bool {
        if (input_id < 0 || input_id >= (int) saved.split0_inputs.size()) {
            return false;
        }

        const auto & entry = saved.split0_inputs[input_id];
        const size_t nbytes = ggml_nbytes(dst);
        if (entry.data.size() < nbytes) {
            return false;
        }

        ggml_backend_sched_tp_tensor_set_from_ram(dst_backend, dst, entry.data.data(), nbytes);
        return true;
    };

    // A Turbo UB must run the same split graph that was present when that UB
    // was captured.  The scheduler's live splits point at the most recently
    // built graph, so restore both the split and the graph-view arrays here.
    auto restore_saved_split_graph = [&]( 
            ggml_backend_sched_tp_saved_ub & saved,
            int split_id) -> bool {
        if (split_id < 0 || split_id >= (int) saved.split_graphs.size()) {
            return false;
        }

        auto & snap = saved.split_graphs[split_id];
        if (snap.split.n_inputs < 0 ||
            snap.split.n_inputs != (int) snap.inputs.size()) {
            return false;
        }

        splits[split_id] = snap.split;
        struct ggml_backend_sched_split * split = &splits[split_id];

        // inputs[] is inline in ggml_backend_sched_split.  Restore it from
        // the owned snapshot rather than relying on the copied struct alone.
        for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
            split->inputs[input_id] = snap.inputs[input_id];
        }

        // snap.split contains the pointers that were live at capture time.
        // Use the owned vectors, whose storage belongs to this saved UB.
        split->graph.nodes   = snap.nodes.data();
        split->graph.n_nodes = (int) snap.nodes.size();
        split->graph.leafs   = snap.leafs.data();
        split->graph.n_leafs = (int) snap.leafs.size();

        for (const auto & node_srcs : snap.node_srcs) {
            if (node_srcs.node == nullptr) {
                continue;
            }
            for (int src_id = 0; src_id < GGML_MAX_SRC; ++src_id) {
                node_srcs.node->src[src_id] = node_srcs.src[src_id];
            }
        }

        return true;
    };

    auto restore_saved_graph_inputs = [&]( 
            const ggml_backend_sched_tp_saved_ub & saved,
            int split_id) -> bool {
        for (const auto & entry : saved.graph_inputs) {
            bool used_by_split = false;
            for (const int saved_split_id : entry.split_ids) {
                if (saved_split_id == split_id) {
                    used_by_split = true;
                    break;
                }
            }
            if (!used_by_split || entry.key == nullptr) {
                continue;
            }

            struct ggml_tensor * input = const_cast<struct ggml_tensor *>(entry.key);
            ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
            if (input_backend == nullptr) {
                return false;
            }

            const size_t nbytes = ggml_nbytes(input);
            if (entry.data.size() < nbytes) {
                return false;
            }

            ggml_backend_sched_tp_tensor_set_from_ram(
                    input_backend, input, entry.data.data(), nbytes);
            ggml_backend_synchronize(input_backend);
        }

        return true;
    };

    auto capture_live_split_snapshots = [&](
            std::vector<ggml_backend_sched_tp_live_split_snapshot> & live_split_snapshots) {
        live_split_snapshots.clear();
        live_split_snapshots.resize(sched->n_splits);

        for (int split_id = 0; split_id < sched->n_splits; ++split_id) {
            const struct ggml_backend_sched_split * live_split = &splits[split_id];
            auto & snap = live_split_snapshots[split_id];
            snap.split = *live_split;
            snap.node_srcs.clear();
            snap.node_srcs.reserve(live_split->graph.n_nodes);

            for (int node_id = 0; node_id < live_split->graph.n_nodes; ++node_id) {
                struct ggml_tensor * node = live_split->graph.nodes[node_id];
                ggml_backend_sched_tp_node_srcs srcs = {};
                srcs.node = node;
                for (int src_id = 0; src_id < GGML_MAX_SRC; ++src_id) {
                    srcs.src[src_id] = node != nullptr ? node->src[src_id] : nullptr;
                }
                snap.node_srcs.push_back(srcs);
            }
        }
    };

    auto restore_live_split_snapshots = [&](
            const std::vector<ggml_backend_sched_tp_live_split_snapshot> & live_split_snapshots) -> bool {
        if ((int) live_split_snapshots.size() < sched->n_splits) {
            return false;
        }

        for (int split_id = 0; split_id < sched->n_splits; ++split_id) {
            splits[split_id] = live_split_snapshots[split_id].split;

            for (const auto & node_srcs : live_split_snapshots[split_id].node_srcs) {
                if (node_srcs.node == nullptr) {
                    continue;
                }
                for (int src_id = 0; src_id < GGML_MAX_SRC; ++src_id) {
                    node_srcs.node->src[src_id] = node_srcs.src[src_id];
                }
            }
        }

        return true;
    };

    auto current_split_input_copy = [&](
            struct ggml_backend_sched_split * split,
            int input_id) -> struct ggml_tensor * {
        if (split == nullptr || input_id < 0 || input_id >= split->n_inputs) {
            return nullptr;
        }
        struct ggml_tensor * input = split->inputs[input_id];
        return input != nullptr
                ? tensor_copy(input, split->backend_id, sched->cur_copy)
                : nullptr;
    };

    auto run_turboprefill_one_split_diagonal = [&](
        ggml_backend_sched_tp_saved_ub & saved,
        int split_id,
        int phase) -> enum ggml_status {
        turboprefill_stage = saved.turboprefill;
        if (!restore_saved_split_graph(saved, split_id)) {
            return GGML_STATUS_FAILED;
        }
        if (!apply_saved_split_tensor_metas(saved, split_id)) {
            return GGML_STATUS_FAILED;
        }

        struct ggml_backend_sched_split * split = &splits[split_id];
        const int split_backend_id = split->backend_id;
        ggml_backend_t split_backend = sched->backends[split_backend_id];

        static ggml_backend_sched_t tp_sched = nullptr;
        static std::vector<ggml_backend_event_t> compute_done_events;
        static std::vector<ggml_backend_event_t> d2h_done_events;
        static std::vector<ggml_backend_event_t> h2d_ready_events;
        static std::vector<bool> compute_started;
        static std::vector<bool> d2h_started;
        static std::vector<bool> h2d_started;
        static std::vector<bool> h2d_ready_recorded;

        if (tp_sched != sched || (int) compute_done_events.size() < sched->n_splits) {
            for (auto ev : compute_done_events) {
                if (ev != nullptr) ggml_backend_event_free(ev);
            }
            for (auto ev : d2h_done_events) {
                if (ev != nullptr) ggml_backend_event_free(ev);
            }
            for (auto ev : h2d_ready_events) {
                if (ev != nullptr) ggml_backend_event_free(ev);
            }
            tp_sched = sched;
            compute_done_events.assign(sched->n_splits, nullptr);
            d2h_done_events.assign(sched->n_splits, nullptr);
            h2d_ready_events.assign(sched->n_splits, nullptr);
            compute_started.assign(sched->n_splits, false);
            d2h_started.assign(sched->n_splits, false);
            h2d_started.assign(sched->n_splits, false);
            h2d_ready_recorded.assign(sched->n_splits, false);

            for (int i = 0; i < sched->n_splits; ++i) {
                const int backend_id = splits[i].backend_id;
                ggml_backend_t backend = sched->backends[backend_id];
                compute_done_events[i] = ggml_backend_event_new(backend);
                d2h_done_events[i]     = ggml_backend_event_new(backend);
                h2d_ready_events[i]    = ggml_backend_event_new(backend);
            }
        }

        if (phase == TP_PHASE_PREPARE_H2D && split_id == 0 && saved.turboprefill == 1) {
            compute_started.assign(sched->n_splits, false);
            d2h_started.assign(sched->n_splits, false);
            h2d_started.assign(sched->n_splits, false);
            h2d_ready_recorded.assign(sched->n_splits, false);
        }

        if (sched->callback_eval) {
            return GGML_STATUS_FAILED;
        }

        if (phase == TP_PHASE_PREPARE_H2D) {
            if (compute_started[split_id] && compute_done_events[split_id] != nullptr) {
                ggml_backend_event_synchronize(compute_done_events[split_id]);
            }

            if (split->n_inputs <= 0) {
                h2d_started[split_id] = true;
                h2d_ready_recorded[split_id] = false;

                return GGML_STATUS_SUCCESS;
            }

            if (split_id > 0) {
                const int prev_split_id = split_id - 1;
                if (!d2h_started[prev_split_id]) {
                    return GGML_STATUS_FAILED;
                }
                if (d2h_done_events[prev_split_id] != nullptr) {
                    ggml_backend_event_synchronize(d2h_done_events[prev_split_id]);
                }
            }

            for (int input_id = 0; input_id < split->n_inputs; ++input_id) {
                struct ggml_tensor * input = split->inputs[input_id];
                struct ggml_tensor * input_cpy = current_split_input_copy(split, input_id);
                if (input == nullptr || input_cpy == nullptr) {
                    return GGML_STATUS_FAILED;
                }
                const auto * plan = saved_input_plan(saved, split_id, input_id);
                if (plan == nullptr || plan->source_kind == GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UNKNOWN) {
                    return GGML_STATUS_FAILED;
                }

                bool load_ok = false;
                switch (plan->source_kind) {
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_SNAPSHOT:
                        load_ok = split_id == 0
                                ? load_saved_split0_input(saved, input_id, split_backend, input_cpy)
                                : load_saved_info_entry(saved, split_id, input, split_backend, input_cpy);
                        break;
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_PREPARED_INPUT:
                        load_ok = load_saved_prepared_input_entry(saved, split_id, input, split_backend, input_cpy);
                        break;
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_LIVE_WEIGHT:
                        load_ok = copy_live_tensor_like_standard(split_backend_id, split_backend, input, input_cpy);
                        break;
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_INTERMEDIATE:
                        load_ok = load_saved_intermediate_entry(saved, split_id, input, split_backend, input_cpy);
                        break;
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_LIVE_INPUT:
                        load_ok = restore_saved_live_input_entry(saved, split_id, input) &&
                                copy_live_tensor_like_standard(split_backend_id, split_backend, input, input_cpy);
                        break;
                    case GGML_BACKEND_SCHED_TP_INPUT_SOURCE_LIVE_CURRENT: {
                        ggml_backend_t input_backend = ggml_backend_sched_get_tensor_backend(sched, input);
                        if (input_backend == nullptr) {
                            load_ok = false;
                            break;
                        }
                        const int input_backend_id = ggml_backend_sched_backend_id(sched, input_backend);
                        ggml_backend_event_t input_event =
                                input_backend_id >= 0 ? sched->events[input_backend_id][sched->cur_copy] : nullptr;
                        ggml_backend_sched_tp_copy_via_ram(
                                sched,
                                sched->n_splits + split_id * GGML_SCHED_MAX_SPLIT_INPUTS + input_id,
                                input_backend,
                                input_event,
                                split_backend,
                                input,
                                input_cpy);
                        load_ok = true;
                        break;
                    }
                    default:
                        load_ok = false;
                        break;
                }

                if (!load_ok) {
                    return GGML_STATUS_FAILED;
                }

            }
            bool h2d_event_recorded = false;
            if (h2d_ready_events[split_id] != nullptr) {
                ggml_backend_event_record(h2d_ready_events[split_id]);
                h2d_event_recorded = true;
            }
            h2d_started[split_id] = true;
            h2d_ready_recorded[split_id] = h2d_event_recorded;

            return GGML_STATUS_SUCCESS;
        }

        if (phase == TP_PHASE_COMPUTE) {

            if (!h2d_started[split_id]) {
                return GGML_STATUS_FAILED;
            }
            if (h2d_ready_recorded[split_id] && h2d_ready_events[split_id] != nullptr) {
                ggml_backend_event_synchronize(h2d_ready_events[split_id]);
            }

            if (!restore_saved_graph_inputs(saved, split_id)) {
                return GGML_STATUS_FAILED;
            }

            enum ggml_status ec = ggml_backend_graph_compute_async(split_backend, &split->graph);
            if (ec != GGML_STATUS_SUCCESS) {
                return ec;
            }

            if (compute_done_events[split_id] != nullptr) {
                ggml_backend_event_record(compute_done_events[split_id]);
            }
            compute_started[split_id] = true;
            h2d_started[split_id] = false;
            h2d_ready_recorded[split_id] = false;

            return GGML_STATUS_SUCCESS;
        }

        if (phase == TP_PHASE_STORE) {

            if (!compute_started[split_id]) {
                return GGML_STATUS_FAILED;
            }
            if (compute_done_events[split_id] != nullptr) {
                ggml_backend_event_synchronize(compute_done_events[split_id]);
            }

            for (int target_split_id = split_id + 1; target_split_id < sched->n_splits; ++target_split_id) {
                if (target_split_id >= (int) saved.input_plans.size()) {
                    continue;
                }

                const auto & plans = saved.input_plans[target_split_id];
                for (int input_id = 0; input_id < (int) plans.size(); ++input_id) {
                    const auto & plan = plans[input_id];
                    if (plan.source_kind != GGML_BACKEND_SCHED_TP_INPUT_SOURCE_UB_INTERMEDIATE ||
                        plan.producer_split_id != split_id ||
                        plan.key == nullptr) {
                        continue;
                    }

                    if (target_split_id >= (int) saved.intermediate_banks.size()) {
                        return GGML_STATUS_FAILED;
                    }

                    ggml_backend_sched_tp_info_entry * entry = nullptr;
                    for (auto & candidate : saved.intermediate_banks[target_split_id]) {
                        if (candidate.key == plan.key) {
                            entry = &candidate;
                            break;
                        }
                    }
                    if (entry == nullptr) {
                        return GGML_STATUS_FAILED;
                    }

                    ggml_backend_t src_backend = ggml_backend_sched_get_tensor_backend(
                            sched, const_cast<struct ggml_tensor *>(plan.key));
                    if (src_backend == nullptr) {
                        return GGML_STATUS_FAILED;
                    }

                    const size_t nbytes = ggml_nbytes(plan.key);
                    entry->data.resize(nbytes);
                    ggml_backend_sched_tp_tensor_get_to_ram(
                            src_backend,
                            nullptr,
                            plan.key,
                            entry->data.data(),
                            nbytes);
                }
            }

            if (d2h_done_events[split_id] != nullptr) {
                ggml_backend_event_record(d2h_done_events[split_id]);
            }

            d2h_started[split_id] = true;

            if (split_id + 1 >= sched->n_splits) {
            }

            return GGML_STATUS_SUCCESS;
        }
        return GGML_STATUS_FAILED;
    };
    if (turboprefill_stage != 0) {
        auto & saved_ubs = ggml_backend_sched_tp_saved_ubs(sched);

        if (turboprefill_stage == 1) {
            saved_ubs.clear();
        }

        const int saved_id = turboprefill_stage > 0 ? turboprefill_stage : -turboprefill_stage;

        if (sched->n_splits > 0) {
            enum ggml_status split0_status = run_standard_split0_capture();
            if (split0_status != GGML_STATUS_SUCCESS) {
                return split0_status;
            }
            const int split0_backend_id = splits[0].backend_id;
            if (split0_backend_id >= 0) {
                ggml_backend_synchronize(sched->backends[split0_backend_id]);
            }
        }
        enum ggml_status split1_prepare_status = prepare_standard_split1_inputs_capture();
        if (split1_prepare_status != GGML_STATUS_SUCCESS) {
            return split1_prepare_status;
        }

        ggml_backend_sched_tp_saved_ub captured = capture_turboprefill_ub(saved_id);
        saved_ubs.push_back(captured);

        if (turboprefill_stage > 0) {
            return GGML_STATUS_SUCCESS;
        }
        std::vector<ggml_backend_sched_tp_tensor_meta> current_metas;
        capture_tensor_tree_meta(current_metas);
        std::vector<ggml_backend_sched_tp_live_split_snapshot> current_live_split_snapshots;
        capture_live_split_snapshots(current_live_split_snapshots);
        auto restore_live_scheduler_state = [&]() -> bool {
            ggml_backend_sched_tp_apply_tensor_metas(current_metas);
            return restore_live_split_snapshots(current_live_split_snapshots);
        };

        const int n_saved = (int) saved_ubs.size();
        const int n_waves = n_saved + sched->n_splits - 1;
        for (int wave = 0; wave < n_waves; ++wave) {
            const int split_max = std::min(wave, sched->n_splits - 1);

            for (int split_id = split_max; split_id >= 0; --split_id) {
                const int saved_index = wave - split_id;
                if (saved_index < 0 || saved_index >= n_saved) {
                    continue;
                }

                auto & saved = saved_ubs[saved_index];
                enum ggml_status split_status = run_turboprefill_one_split_diagonal(
                        saved,
                        split_id,
                        TP_PHASE_PREPARE_H2D);
                if (split_status != GGML_STATUS_SUCCESS) {
                    if (!restore_live_scheduler_state()) {
                        return GGML_STATUS_FAILED;
                    }
                    return split_status;
                }
            }

            for (int split_id = split_max; split_id >= 0; --split_id) {
                const int saved_index = wave - split_id;
                if (saved_index < 0 || saved_index >= n_saved) {
                    continue;
                }

                auto & saved = saved_ubs[saved_index];
                enum ggml_status split_status = run_turboprefill_one_split_diagonal(
                        saved,
                        split_id,
                        TP_PHASE_COMPUTE);
                if (split_status != GGML_STATUS_SUCCESS) {
                    if (!restore_live_scheduler_state()) {
                        return GGML_STATUS_FAILED;
                    }
                    return split_status;
                }
            }

            for (int split_id = split_max; split_id >= 0; --split_id) {
                const int saved_index = wave - split_id;
                if (saved_index < 0 || saved_index >= n_saved) {
                    continue;
                }

                auto & saved = saved_ubs[saved_index];
                enum ggml_status split_status = run_turboprefill_one_split_diagonal(
                        saved,
                        split_id,
                        TP_PHASE_STORE);
                if (split_status != GGML_STATUS_SUCCESS) {
                    if (!restore_live_scheduler_state()) {
                        return GGML_STATUS_FAILED;
                    }
                    return split_status;
                }
            }
        }

        ggml_backend_sched_synchronize(sched);

        if (!restore_live_scheduler_state()) {
            return GGML_STATUS_FAILED;
        }

        saved_ubs.clear();

        return GGML_STATUS_SUCCESS;
    }
    const int n_splits = sched->n_splits;
    enum ggml_status split_status = run_split_range(0, n_splits, 1);
    if (split_status != GGML_STATUS_SUCCESS) {
        return split_status;
    }

    return GGML_STATUS_SUCCESS;
}

ggml_backend_sched_t ggml_backend_sched_new(
        ggml_backend_t * backends,
        ggml_backend_buffer_type_t * bufts,
        int n_backends,
        size_t graph_size,
        bool parallel) {
    GGML_ASSERT(n_backends > 0);
    GGML_ASSERT(n_backends <= GGML_SCHED_MAX_BACKENDS);
    GGML_ASSERT(ggml_backend_is_cpu(backends[n_backends - 1])); // last backend must be CPU

    struct ggml_backend_sched * sched = (ggml_backend_sched *)calloc(1, sizeof(struct ggml_backend_sched));

    for (int i = 0; i < (GGML_OP_COUNT + 31)/32; ++i) sched->op_offload[i] = 0xffffffff;

    sched->debug = getenv("GGML_SCHED_DEBUG") != NULL;
    sched->n_backends = n_backends;
    sched->n_copies = parallel ? GGML_SCHED_MAX_COPIES : 1;
    sched->tp_ram_slots = nullptr;
    sched->tp_ram_slots_count = 0;
    sched->tp_saved_ubs = nullptr;

    // initialize hash table
    // FIXME: needs to be size*2 to account for leafs (do it in graph_split instead)
    sched->hash_set    = ggml_hash_set_new(graph_size);
    sched->hv_tensor_backend_ids = (int *)malloc(sched->hash_set.size * sizeof(sched->hv_tensor_backend_ids[0]));
    sched->hv_tensor_copies      = (ggml_tensor **)malloc(sched->hash_set.size * sched->n_backends * sched->n_copies * sizeof(struct ggml_tensor *));

    const size_t nodes_size = graph_size + GGML_SCHED_MAX_SPLITS*GGML_SCHED_MAX_SPLIT_INPUTS*2;
    sched->node_backend_ids = (int *)calloc(nodes_size, sizeof(sched->node_backend_ids[0]));
    sched->leaf_backend_ids = (int *)calloc(nodes_size, sizeof(sched->leaf_backend_ids[0]));
    sched->prev_node_backend_ids = (int *)calloc(nodes_size, sizeof(sched->prev_node_backend_ids[0]));
    sched->prev_leaf_backend_ids = (int *)calloc(nodes_size, sizeof(sched->prev_leaf_backend_ids[0]));

    sched->context_buffer_size = GGML_SCHED_MAX_SPLITS*GGML_SCHED_MAX_SPLIT_INPUTS*2*sizeof(struct ggml_tensor) + ggml_graph_overhead_custom(graph_size, false);
    sched->context_buffer = (char *)malloc(sched->context_buffer_size);

    const int initial_splits_capacity = 16;
    sched->splits = (ggml_backend_sched_split *)calloc(initial_splits_capacity, sizeof(sched->splits[0]));
    sched->splits_capacity = initial_splits_capacity;

    for (int b = 0; b < n_backends; b++) {
        sched->backends[b] = backends[b];
        sched->bufts[b] = bufts ? bufts[b] : ggml_backend_get_default_buffer_type(backends[b]);
        GGML_ASSERT(ggml_backend_supports_buft(backends[b], sched->bufts[b]));
        if (sched->n_copies > 1) {
            for (int c = 0; c < sched->n_copies; c++) {
                sched->events[b][c] = ggml_backend_event_new(backends[b]);
            }
        }
    }

    sched->galloc = ggml_gallocr_new_n(sched->bufts, n_backends);

    sched->workers.reserve(sched->n_backends);
    sched->statuses.resize(sched->n_backends, GGML_STATUS_SUCCESS);
    sched->backend_splits.resize(sched->n_backends);

    ggml_backend_sched_reset(sched);

    return sched;
}

void ggml_backend_sched_free(ggml_backend_sched_t sched) {
    if (sched == NULL) {
        return;
    }
    for (int b = 0; b < sched->n_backends; b++) {
        for (int c = 0; c < sched->n_copies; c++) {
            ggml_backend_event_free(sched->events[b][c]);
        }
    }
    for (int i = 0; i < sched->n_backends; ++i) {
        if (sched->input_memory_bufs[i]) {
            ggml_backend_buffer_free(sched->input_memory_bufs[i]);
        }
    }
    ggml_gallocr_free(sched->galloc);
    ggml_free(sched->ctx);
    ggml_hash_set_free(&sched->hash_set);
    free(sched->splits);
    free(sched->hv_tensor_backend_ids);
    free(sched->hv_tensor_copies);
    free(sched->node_backend_ids);
    free(sched->leaf_backend_ids);
    free(sched->prev_node_backend_ids);
    free(sched->prev_leaf_backend_ids);
    free(sched->context_buffer);
    free(sched->graph.nodes);
    free(sched->graph.leafs);
    delete[] sched->tp_ram_slots;
    delete sched->tp_saved_ubs;
    free(sched);
}

void ggml_backend_sched_reset(ggml_backend_sched_t sched) {
    // reset state for the next run
    if (!sched->is_reset) {
        ggml_hash_set_reset(&sched->hash_set);
        memset(sched->hv_tensor_backend_ids, -1, sched->hash_set.size * sizeof(sched->hv_tensor_backend_ids[0]));
        memset(sched->hv_tensor_copies,       0, sched->hash_set.size * sched->n_backends * sched->n_copies * sizeof(struct ggml_tensor *));
        sched->is_reset = true;
    }
    sched->is_alloc = false;
}

bool ggml_backend_sched_reserve(ggml_backend_sched_t sched, struct ggml_cgraph * measure_graph) {
    GGML_ASSERT((int)sched->hash_set.size >= measure_graph->n_nodes + measure_graph->n_leafs);
    ggml_backend_sched_synchronize(sched);

    ggml_backend_sched_split_graph(sched, measure_graph);

    if (!ggml_gallocr_reserve_n(sched->galloc, &sched->graph, sched->node_backend_ids, sched->leaf_backend_ids)) {
        return false;
    }

    ggml_backend_sched_reset(sched);

    return true;
}

static void ggml_sched_prepare_graph(ggml_backend_sched_t sched) {

    for (auto & item : sched->own_cpy   ) item = false;
    for (auto & item : sched->needs_sync) item = true;

    if (sched->split_mode_graph) {
        auto tensor_size = [] (const ggml_tensor * t) {
            auto nbytes = ggml_nbytes(t);
            nbytes = 256*((nbytes + 255)/256);
            return nbytes;
        };
        //auto tim1 = std::chrono::steady_clock::now();
        for (auto & b : sched->backend_splits) b.clear();
        for (int i = 0; i < sched->n_splits; i++) {
            sched->backend_splits[sched->splits[i].backend_id].push_back(&sched->splits[i]);
        }
        for (int backend_id = 0; backend_id < sched->n_backends; ++backend_id) {
            if (ggml_backend_is_cpu(ggml_backend_sched_get_backend(sched, backend_id))) continue;
            if (sched->backend_splits[backend_id].empty()) continue;
            size_t input_size = 0;
            size_t max_input_size = 0;
            int last_split = 0;
            bool can_alloc = true;
            for (int i = 0; i < int(sched->backend_splits[backend_id].size()); ++i) {
                auto split = sched->backend_splits[backend_id][i];
                if (split->n_inputs < 1) continue;
                size_t this_size = 0;
                for (int j = 0; j < split->n_inputs; ++j) {
                    if (!ggml_backend_buffer_is_host(split->inputs[j]->buffer)) {
                        this_size += tensor_size(split->inputs[j]);
                    }
                }
                if (input_size + this_size > sched->max_extra_alloc) {
                    if (i - last_split < 3) {
                        can_alloc = false;
                        break;
                    }
                    max_input_size = std::max(max_input_size, input_size);
                    input_size = 0;
                    last_split = i - 1;
                }
                input_size += this_size;
            }
            max_input_size = std::max(max_input_size, input_size);
            if (!can_alloc || !max_input_size) continue;
            if (sched->input_memory_bufs[backend_id] && sched->input_memory_bufs[backend_id]->size < max_input_size) {
                ggml_backend_buffer_free(sched->input_memory_bufs[backend_id]);
                sched->input_memory_bufs[backend_id] = nullptr;
            }
            if (!sched->input_memory_bufs[backend_id]) {
                sched->input_memory_bufs[backend_id] = ggml_backend_alloc_buffer(sched->backends[backend_id], max_input_size);
            }
            auto ptr = (char *)ggml_backend_buffer_get_base(sched->input_memory_bufs[backend_id]);
            input_size = 0;
            for (int i = 0; i < int(sched->backend_splits[backend_id].size()); ++i) {
                auto split = sched->backend_splits[backend_id][i];
                size_t this_size = 0;
                for (int j = 0; j < split->n_inputs; ++j) {
                    if (!ggml_backend_buffer_is_host(split->inputs[j]->buffer)) {
                        this_size += tensor_size(split->inputs[j]);
                    }
                }
                if (input_size + this_size > max_input_size) {
                    ptr = (char *)ggml_backend_buffer_get_base(sched->input_memory_bufs[backend_id]);
                    input_size = 0;
                }
                for (int j = 0; j < split->n_inputs; ++j) {
                    if (ggml_backend_buffer_is_host(split->inputs[j]->buffer)) continue;
                    auto input_cpy = tensor_copy(split->inputs[j], backend_id, sched->cur_copy);
                    for (int k = 0; k < split->graph.n_nodes; ++k) {
                        auto node = split->graph.nodes[k];
                        for (int l = 0; l < GGML_MAX_SRC; ++l) {
                            if (node->src[l] && node->src[l]->data == input_cpy->data) node->src[l]->data = ptr;
                        }
                    }
                    input_cpy->data = ptr;
                    ptr += tensor_size(split->inputs[j]);
                }
                input_size += this_size;
            }
            sched->needs_sync[backend_id] = false;
            sched->own_cpy[backend_id] = true;
        }
    }
}

bool ggml_backend_sched_alloc_graph(ggml_backend_sched_t sched, struct ggml_cgraph * graph) {
    GGML_ASSERT((int)sched->hash_set.size >= graph->n_nodes + graph->n_leafs);

    ggml_backend_sched_split_graph(sched, graph);

    if (!ggml_backend_sched_alloc_splits(sched)) {
        return false;
    }
    ggml_sched_prepare_graph(sched);

    sched->is_alloc = true;

    return true;
}

enum ggml_status ggml_backend_sched_graph_compute(ggml_backend_sched_t sched, struct ggml_cgraph * graph) {
    enum ggml_status err = ggml_backend_sched_graph_compute_async(sched, graph);
    ggml_backend_sched_synchronize(sched);
    return err;
}

enum ggml_status ggml_backend_sched_graph_compute_async_turboprefill(
        ggml_backend_sched_t sched,
        struct ggml_cgraph * graph,
        int turboprefill_stage) {
    if (!sched->is_reset && !sched->is_alloc) {
        ggml_backend_sched_reset(sched);
    }

    if (!sched->is_alloc) {
        if (!ggml_backend_sched_alloc_graph(sched, graph)) {
            return GGML_STATUS_ALLOC_FAILED;
        }
    }

    return ggml_backend_sched_compute_splits_turboprefill(sched, turboprefill_stage);
}

enum ggml_status ggml_backend_sched_graph_compute_async(ggml_backend_sched_t sched, struct ggml_cgraph * graph) {
    if (!sched->is_reset && !sched->is_alloc) {
        ggml_backend_sched_reset(sched);
    }

    if (!sched->is_alloc) {
        if (!ggml_backend_sched_alloc_graph(sched, graph)) {
            return GGML_STATUS_ALLOC_FAILED;
        }
    }

    return ggml_backend_sched_compute_splits(sched);
}

void ggml_backend_sched_synchronize(ggml_backend_sched_t sched) {
    for (int i = 0; i < sched->n_backends; i++) {
        ggml_backend_synchronize(sched->backends[i]);
    }
}

void ggml_backend_sched_set_eval_callback(ggml_backend_sched_t sched, ggml_backend_sched_eval_callback callback, void * user_data) {
    sched->callback_eval = callback;
    sched->callback_eval_user_data = user_data;
}

int ggml_backend_sched_get_n_splits(ggml_backend_sched_t sched) {
    return sched->n_splits;
}

int ggml_backend_sched_get_n_copies(ggml_backend_sched_t sched) {
    return sched->n_copies;
}

int ggml_backend_sched_get_n_backends(ggml_backend_sched_t sched) {
    return sched->n_backends;
}

ggml_backend_t ggml_backend_sched_get_backend(ggml_backend_sched_t sched, int i) {
    GGML_ASSERT(i >= 0 && i < sched->n_backends);
    return sched->backends[i];
}

int ggml_backend_sched_get_backend_idx(ggml_backend_sched_t sched, ggml_backend_buffer_t buffer) {
    if (!buffer || !buffer->buft) return -1;
    if (buffer && buffer->buft) {
        for (int i = 0; i < sched->n_backends; ++i) {
            if (ggml_backend_get_default_buffer_type(sched->backends[i]) == buffer->buft) return i;
        }
    }
    return -1;
}

size_t ggml_backend_sched_get_buffer_size(ggml_backend_sched_t sched, ggml_backend_t backend) {
    int backend_index = ggml_backend_sched_backend_id(sched, backend);
    GGML_ASSERT(backend_index >= 0 && backend_index < sched->n_backends);

    return ggml_gallocr_get_buffer_size(sched->galloc, backend_index);
}

void ggml_backend_sched_set_tensor_backend(ggml_backend_sched_t sched, struct ggml_tensor * node, ggml_backend_t backend) {
    int backend_index = ggml_backend_sched_backend_id(sched, backend);
    GGML_ASSERT(backend_index >= 0 && backend_index < sched->n_backends);
    tensor_backend_id(node) = backend_index;
    SET_CAUSE(node, "usr");
    sched->is_reset = false;
}

ggml_backend_t ggml_backend_sched_get_tensor_backend(ggml_backend_sched_t sched, struct ggml_tensor * node) {
    int backend_index = tensor_backend_id(node);
    if (backend_index == -1) {
        if (node->buffer && node->buffer->buft) {
            for (int i = 0; i < sched->n_backends; ++i) {
                if (sched->backends[i]->iface.get_default_buffer_type(sched->backends[i]) == node->buffer->buft) {
                    return sched->backends[i];
                }
            }
        }
        return nullptr;
    }
    return sched->backends[backend_index];
}

// utils

void ggml_backend_view_init(struct ggml_tensor * tensor) {
    GGML_ASSERT(tensor->buffer == NULL);
    GGML_ASSERT(tensor->view_src != NULL);
    GGML_ASSERT(tensor->view_src->buffer != NULL);
    GGML_ASSERT(tensor->view_src->data != NULL);

    tensor->buffer = tensor->view_src->buffer;
    tensor->data = (char *)tensor->view_src->data + tensor->view_offs;
    ggml_backend_buffer_init_tensor(tensor->buffer, tensor);
}

void ggml_backend_tensor_alloc(ggml_backend_buffer_t buffer, struct ggml_tensor * tensor, void * addr) {
    GGML_ASSERT(tensor->buffer == NULL);
    GGML_ASSERT(tensor->data == NULL);
    GGML_ASSERT(tensor->view_src == NULL);
    GGML_ASSERT(addr >= ggml_backend_buffer_get_base(buffer));
    GGML_ASSERT((char *)addr + ggml_backend_buffer_get_alloc_size(buffer, tensor) <=
                (char *)ggml_backend_buffer_get_base(buffer) + ggml_backend_buffer_get_size(buffer));

    tensor->buffer = buffer;
    tensor->data = addr;
    ggml_backend_buffer_init_tensor(buffer, tensor);
}

static struct ggml_tensor * graph_copy_dup_tensor(struct ggml_hash_set hash_set, struct ggml_tensor ** node_copies,
    struct ggml_context * ctx_allocated, struct ggml_context * ctx_unallocated, struct ggml_tensor * src) {

    GGML_ASSERT(src != NULL);
    GGML_ASSERT(src->data && "graph must be allocated");

    size_t id = ggml_hash_insert(&hash_set, src);
    if (id == GGML_HASHSET_ALREADY_EXISTS) {
        return node_copies[ggml_hash_find(&hash_set, src)];
    }

    struct ggml_tensor * dst = ggml_dup_tensor_layout(src->data && !src->view_src ? ctx_allocated : ctx_unallocated, src);
    if (src->view_src != NULL) {
        dst->view_src = graph_copy_dup_tensor(hash_set, node_copies, ctx_allocated, ctx_unallocated, src->view_src);
        dst->view_offs = src->view_offs;
    }
    dst->op = src->op;
    memcpy(dst->op_params, src->op_params, sizeof(dst->op_params));
    ggml_set_name(dst, src->name);

    // copy src
    for (int i = 0; i < GGML_MAX_SRC; i++) {
        struct ggml_tensor * s = src->src[i];
        if (s == NULL) {
            continue;
        }
        dst->src[i] = graph_copy_dup_tensor(hash_set, node_copies, ctx_allocated, ctx_unallocated, s);
    }

    node_copies[id] = dst;
    return dst;
}

static void graph_copy_init_tensor(struct ggml_hash_set * hash_set, struct ggml_tensor ** node_copies, bool * node_init, struct ggml_tensor * src) {
    size_t id = ggml_hash_find(hash_set, src);
    if (node_init[id]) {
        return;
    }
    node_init[id] = true;

    struct ggml_tensor * dst = node_copies[id];
    if (dst->view_src != NULL) {
        graph_copy_init_tensor(hash_set, node_copies, node_init, src->view_src);
        ggml_backend_view_init(dst);
    }
    else {
        ggml_backend_tensor_copy(src, dst);
    }

    // init src
    for (int i = 0; i < GGML_MAX_SRC; i++) {
        struct ggml_tensor * s = src->src[i];
        if (s == NULL) {
            continue;
        }
        graph_copy_init_tensor(hash_set, node_copies, node_init, s);
    }
}

struct ggml_backend_graph_copy ggml_backend_graph_copy(ggml_backend_t backend, struct ggml_cgraph * graph) {
    struct ggml_hash_set hash_set = ggml_hash_set_new(graph->visited_hash_set.size);
    struct ggml_tensor ** node_copies = (ggml_tensor **)calloc(hash_set.size, sizeof(node_copies[0])); // NOLINT
    bool * node_init = (bool *)calloc(hash_set.size, sizeof(node_init[0]));

    struct ggml_init_params params = {
        /* .mem_size   = */ ggml_tensor_overhead()*hash_set.size + ggml_graph_overhead_custom(graph->size, false),
        /* .mem_buffer = */ NULL,
        /* .no_alloc   = */ true
    };

    struct ggml_context * ctx_allocated = ggml_init(params);
    struct ggml_context * ctx_unallocated = ggml_init(params);

    if (ctx_allocated == NULL || ctx_unallocated == NULL) {
        fprintf(stderr, "failed to allocate context for graph copy\n");
        ggml_hash_set_free(&hash_set);
        free(node_copies);
        free(node_init);
        ggml_free(ctx_allocated);
        ggml_free(ctx_unallocated);
        return {
            /* .buffer           = */ NULL,
            /* .ctx_allocated    = */ NULL,
            /* .ctx_unallocated  = */ NULL,
            /* .graph            = */ NULL,
        };
    }

    // dup nodes
    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        graph_copy_dup_tensor(hash_set, node_copies, ctx_allocated, ctx_unallocated, node);
    }

    // allocate nodes
    ggml_backend_buffer_t buffer = ggml_backend_alloc_ctx_tensors(ctx_allocated, backend);
    if (buffer == NULL) {
        fprintf(stderr, "failed to allocate buffer for graph copy\n");
        ggml_hash_set_free(&hash_set);
        free(node_copies);
        free(node_init);
        ggml_free(ctx_allocated);
        ggml_free(ctx_unallocated);
        return {
            /* .buffer           = */ NULL,
            /* .ctx_allocated    = */ NULL,
            /* .ctx_unallocated  = */ NULL,
            /* .graph            = */ NULL,
        };
    }

    //printf("copy buffer size: %zu MB\n", ggml_backend_buffer_get_size(buffer) / 1024 / 1024);

    // copy data and init views
    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        graph_copy_init_tensor(&hash_set, node_copies, node_init, node);
    }

    // build graph copy
    struct ggml_cgraph * graph_copy = ggml_new_graph_custom(ctx_allocated, graph->size, false);
    for (int i = 0; i < graph->n_nodes; i++) {
        struct ggml_tensor * node = graph->nodes[i];
        struct ggml_tensor * node_copy = node_copies[ggml_hash_find(&hash_set, node)];
        graph_copy->nodes[i] = node_copy;
    }
    graph_copy->n_nodes = graph->n_nodes;

    ggml_hash_set_free(&hash_set);
    free(node_copies);
    free(node_init);

    return {
        /* .buffer           = */ buffer,
        /* .ctx_allocated    = */ ctx_allocated,
        /* .ctx_unallocated  = */ ctx_unallocated,
        /* .graph            = */ graph_copy,
    };
}

void ggml_backend_graph_copy_free(struct ggml_backend_graph_copy copy) {
    ggml_backend_buffer_free(copy.buffer);
    ggml_free(copy.ctx_allocated);
    ggml_free(copy.ctx_unallocated);
}

bool ggml_backend_compare_graph_backend(ggml_backend_t backend1, ggml_backend_t backend2, struct ggml_cgraph * graph, ggml_backend_eval_callback callback, void * user_data) {
    struct ggml_backend_graph_copy copy = ggml_backend_graph_copy(backend2, graph);
    if (copy.buffer == NULL) {
        return false;
    }

    struct ggml_cgraph * g1 = graph;
    struct ggml_cgraph * g2 = copy.graph;

    assert(g1->n_nodes == g2->n_nodes);

    for (int i = 0; i < g1->n_nodes; i++) {
        //printf("eval %d/%d\n", i, g1->n_nodes);
        struct ggml_tensor * t1 = g1->nodes[i];
        struct ggml_tensor * t2 = g2->nodes[i];

        assert(t1->op == t2->op && ggml_are_same_layout(t1, t2));

        struct ggml_cgraph g1v = ggml_graph_view(g1, i, i + 1);
        struct ggml_cgraph g2v = ggml_graph_view(g2, i, i + 1);

        ggml_backend_graph_compute(backend1, &g1v);
        ggml_backend_graph_compute(backend2, &g2v);

        if (ggml_is_view_op(t1->op)) {
            continue;
        }

        // compare results, calculate rms etc
        if (!callback(i, t1, t2, user_data)) {
            break;
        }
    }

    ggml_backend_graph_copy_free(copy);

    return true;
}
