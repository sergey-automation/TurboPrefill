## How a Sawmill Helped Speed Up AI.

![TurboPrefill](https://raw.githubusercontent.com/sergey-automation/TurboPrefill/main/stories/TurboPrefill_GoldWood.png)

## Observation

For more than 20 years I have been finding and eliminating bottlenecks in factories, production lines, machine tools, and automation systems.

In industry, I often saw that system performance is determined not only by the power of individual units, but also by how the workflow between them is organized.

Recently, I was simply playing with an old mining rig built from 10 NVIDIA P104-100 GPUs.

I ran GPT-OSS-120B on it using llama.cpp.

## The Sawmill Analogy

While watching GPU utilization, I noticed a strange picture. Despite having ten GPUs, at any given moment only one GPU was doing most of the work, while the others were waiting for their turn.

This looked surprisingly familiar.

I had seen something similar on one of my sawmill production lines, where a log passes through several machines sequentially: while one machine is working, the rest of the line sits idle.

Just like on the sawmill line, I decided to feed the "tree trunks" more densely.

## But first, a little theory.

llama.cpp has a mode that splits a model across multiple GPUs by layers. This makes it possible to distribute a large model across the VRAM of several GPUs when a single GPU does not have enough memory.

Each GPU processes its own part of the data and then passes the already "chewed" data to the next GPU. It is important that the data passes through the layers strictly in sequence — from the first layer to the last. Later data must not overtake earlier data.

Continuing the sawmill analogy, the next tree trunk had to wait until the previous tree trunk passed through every machine in the line.

For the "decode" stage this is indeed a necessary condition — generating the next token requires the previous one.

For the "prefill" stage, however, this is not necessary. A tree trunk can be fed into a machine as soon as the previous tree trunk has cleared that machine, without waiting for it to pass through all the remaining machines in the line. The only requirement is to preserve the correct order.

## The Idea

This is how TurboPrefill was born — a mechanism called "Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill".

To avoid breaking existing mechanisms, I added two things to llama.cpp:

1. A "sorting table" that selects and accumulates suitable "tree trunks" (micro-batches (UB) belonging to a batch (B)).
2. A separate turbo pipeline into which "tree trunks" can be fed more densely.

The difference from the standard pipeline is that each machine has its own table where a tree trunk can sit and wait until the machine becomes available.

In the standard pipeline there is only one table shared by all GPUs, and it effectively "runs" from machine to machine as the tree trunk progresses through the line.

"Tree trunks" that did not meet the required conditions were sent to the regular pipeline.

In the first implementation:

https://github.com/sergey-automation/TurboPrefill

I used strict selection criteria and only accepted "tree trunks containing text data only".

## Implementations

In the next implementation:

https://github.com/sergey-automation/TurboPrefill-VLM-Validation

I relaxed the selection criteria and, in addition to text data, started accepting "visual" data as well — situations where a user uploads an image (or screenshot) and asks the AI to answer questions about it.

## Results

As a result, the responsiveness of AI interactions improved significantly. The waiting time between asking a question and receiving the beginning of an answer was reduced **by 1.6× for two-GPU pipelines and by up to 2.2× for eight-GPU pipelines**.

For example, if you upload a screenshot of an error and ask how to fix it, or upload a document and ask for a brief explanation of its contents, TurboPrefill allows the answer to begin several seconds sooner. The larger the document, image, or request, the greater the time savings compared to the standard pipeline.

The speedup is achieved entirely through scheduling. The mathematics and logic of the model remain unchanged and do not affect answer quality.

The mechanism itself is not tied to any particular GPU architecture. It has been tested on several GPU generations — from Pascal (GTX 1080, P104-100) to Ampere (RTX 3090) and Blackwell (RTX 5060 Ti).

## Links

I proposed, introduced, and described the "Intra-Prompt Pipeline Scheduling for Multi-GPU Prefill" mechanism here:
https://github.com/ggml-org/llama.cpp/pull/24219

And created several implementations:

https://github.com/sergey-automation/TurboPrefill

https://github.com/sergey-automation/TurboPrefill-VLM-Validation

The project is evolving. I invite you to participate in testing.

Best regards,
Serhii Trykhlieb

