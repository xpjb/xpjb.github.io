---
layout: experiment
title: "Can LLVM + Ghidra make better source code?"
description: "A reproducible experiment: optimize three real C libraries with LLVM, decompile with Ghidra, and measure source size, correctness, machine code, and speed."
permalink: /blog/llvm-ghidra-source-transformation/
---
<article class="experiment-report" markdown="1">

[← Writings](/writings.html)

<p class="kicker">An actual compiler experiment · October 8, 2026</p>

# Can LLVM + Ghidra make better source code?

<p class="deck">Take real C code, turn LLVM's optimization up, then decompile the result back into C. Does the compiler's hard work become a shorter, faster, or more elegant program?</p>

The idea is appealing. LLVM knows how to fold constants, remove redundant work, inline functions, and simplify control flow. Perhaps Ghidra could turn that optimized machine code back into an improved source representation.

So this experiment actually ran that pipeline on **a JSON parser, an image codec, and a SHA-256 implementation**—then tried to compile and test the output, rather than just judging screenshots.

> **The short answer:** not a useful automatic source simplifier in these tests. The `-O3` decompilations had **1.50×, 2.03×, and 2.98×** as many source tokens as their original implementations. Mechanically recompiled code could silently change behavior. After explicit semantic repairs, one parser was **27 machine-code bytes smaller** and had a **2.5% lower median runtime** on one workload. That is a small, qualified win—not a general source-optimization technique.

[Download the complete experiment](/assets/experiments/llvm-ghidra-2026/experiment.tar.gz), including pinned upstream source, build scripts, untouched Ghidra output, repair diffs, tests, binaries, and raw measurements. No Ghidra installation is bundled.

## 1. What was tested

These are complete algorithm implementations, not specially constructed arithmetic tricks:

| Implementation | Work performed | Pinned upstream commit |
| --- | --- | --- |
| [jsmn](https://github.com/zserge/jsmn) | JSON tokenization, strict mode | `25647e692c79` |
| [QOI](https://github.com/phoboslab/qoi) | Image encoding and decoding | `ffb2d2cb74a1` |
| [Brad Conte's SHA-256](https://github.com/B-Con/crypto-algorithms) | Streaming cryptographic hash | `cfbde48414ba` |

The SHA implementation is educational, not an optimized production cryptographic library. QOI's file-I/O wrappers were disabled; its encoder and decoder were retained. No algorithm bodies were rewritten before optimization.

The setup was **Clang/LLVM/LLD 22.1.8**, **Ghidra 12.1.4**, and an **AMD Ryzen 5 5600X**, running x86-64 Linux. Ghidra was run headlessly with automatic analysis and its C decompiler.

### What does “maximum LLVM optimization” mean?

There is no universal “enable every optimization and get the best program” setting. The main speed-oriented configuration was:

```sh
clang -O3 -flto -march=native ...
```

That means aggressive optimization, full link-time optimization, and instructions tuned for the host CPU. The main comparison also included `-O0`, `-O2`, and **`-Oz`**, because optimizing for speed is not the same objective as optimizing for size.

Additional controls used generic x86-64, explicit `-funroll-loops`, and full debugging information. **Adding `-funroll-loops` produced byte-identical `.text` to ordinary `-O3` here.** PGO and an exhaustive search over optimization pass orders were not attempted.

The implementations were built as shared libraries retaining their public APIs. The separate benchmark driver called those APIs through dynamically resolved function pointers. This prevented the optimizer from seeing the benchmark input and replacing the workload with a precomputed answer.

<details markdown="1">
<summary>Exact common flags and important semantic choices</summary>

```sh
-std=c11 -shared -fPIC -fuse-ld=lld -flto -march=native -g0
-Wl,-Bsymbolic -fno-stack-protector -fwrapv -fno-strict-aliasing
```

All original and round-trip builds used these common choices. The generic control overrides `-march=native`; the debug controls override `-g0`.

* `-fwrapv` matters: the unmodified SHA implementation contains a promoted signed left shift that UBSan diagnoses without this flag. The included probe records that original-source issue separately from decompiler errors. This experiment uses Clang's wrapping behavior, not a claim that the upstream source is strictly portable ISO C.
* `-fno-strict-aliasing` makes the comparison more accommodating to the pointer reinterpretations in the generated source.
* Stack-protector instrumentation was excluded to avoid measuring reconstruction of security scaffolding. This is an experimental choice, not deployment advice.
* No fast-math flags were used; these workloads are integer code.

[Full build commands](/assets/experiments/llvm-ghidra-2026/build_commands.json)

</details>

## 2. Shorter machine code did not mean shorter source

First, the compiler did useful work. These are **function machine-code bytes**, summed across each implementation and its surviving private helpers:

| Library | Original at `-O0` | Original at `-O3` | Original at `-Oz` |
| --- | ---: | ---: | ---: |
| jsmn | 2,449 | 1,495 | 1,256 |
| QOI | 2,845 | 1,981 | 2,063 |
| SHA-256 | 1,840 | 1,428 | 753 |

These counts exclude alignment padding, constant tables, ELF headers, startup code, and external libc. They are not total executable sizes. Notice that even the size-oriented setting does not win every individual library: QOI was smaller at `-O3` in this run.

Now look at the **source text** recovered from those binaries:

| Library | Original C | Ghidra from `-O0` | Ghidra from `-O3` | Ghidra from `-Oz` |
| --- | ---: | ---: | ---: | ---: |
| jsmn | 1,493 | 2,217 | 2,235 | 1,986 |
| QOI | 1,754 | 2,848 | 3,562 | 3,611 |
| SHA-256 | 1,028 | 2,052 | 3,065 | 1,723 |

![C lexical token counts: all three original implementations are shorter than their O3 and Oz decompilations.](/assets/experiments/llvm-ghidra-2026/source-growth.svg)

These are **C lexical tokens inside function definitions**, not file sizes or whitespace-sensitive line counts. Comments and inactive conditional branches are removed. Type declarations, standalone prototypes, constant tables, and compatibility helpers are excluded on both sides. Excluding the decompiler's support code actually favors its result; these are not counts of everything required to rebuild it.

Macros give the original source an abstraction advantage. Counting the original functions **after macro expansion** reduces the `-O3` growth factors to **1.42×, 1.80×, and 2.24×**. It does not reverse the result.

The clearest example is SHA-256: `-Oz` nearly halves its machine-code size relative to `-O3`, but its recovered source is still larger than the original. Binary compactness and source compactness are different measurements.

[Source metrics](/assets/experiments/llvm-ghidra-2026/source_metrics.json) · [Untouched O3 parser](/assets/experiments/llvm-ghidra-2026/raw/jsmn-O3.c) · [Untouched O3 codec](/assets/experiments/llvm-ghidra-2026/raw/qoi-O3.c) · [Untouched O3 hash](/assets/experiments/llvm-ghidra-2026/raw/sha256-O3.c)

## 3. What actually happens to the code?

### Inlining removes helpers, not necessarily complexity

jsmn went from **six source functions to two retained functions**: parse and initialize. Helper logic was folded into the parser. But the original implementation's **one `goto` became 23** in the `-O3` decompilation, and its token count increased by about 50%.

Fewer functions is not automatically less code, and compiler control-flow simplification does not necessarily reconstruct into simpler C control flow.

### SIMD becomes instruction-shaped pseudocode

Some QOI header-writing operations became vector instructions. Ghidra recovered sequences such as:

```c
auVar6 = vpshufd_avx(ZEXT416(uVar25),0x50);
auVar7 = vpermq_avx2(ZEXT1632(auVar6),0x50);
auVar7 = vpsrlvd_avx2(auVar7,_DAT_001009c0);
```

This exposes the optimized implementation, but it is not a nicer expression of an image-file header. The output also contains generated temporaries, lane selections such as `._0_16_`, and array assignments that are not ordinary compilable C.

Avoiding AVX was not a universal cure. The generic x86-64 QOI decompilation grew to **5,189 tokens**, versus **3,562** for native `-O3`.

### There were small local reductions

`sha256_init` went from **93 to 88 tokens**. Several 32-bit state initializations became wider stores: ten assignments became six. However, its non-whitespace character count grew from **262 to 291**, and descriptive member accesses became numeric offsets.

So even this little example answers “shorter?” differently depending on the metric. The compiler had already made those wider stores in the original optimized binary; decompiling did not create that optimization.

### What if Ghidra gets the original type information?

Since the source is available, throwing away all debugging information is an unfavorable setup for a source transformer. A second pass supplied full DWARF. The debug and non-debug builds had **identical `.text` bytes**, so this isolated the effect of information available to Ghidra.

With debug information, `-O3` output contained **2,047 tokens for jsmn, 3,582 for QOI, and 3,221 for SHA-256**. Names and some structure fields became more recognizable, but none became shorter than the original implementation. Ghidra also reported unrecoverable optimized DWARF locations; this was the actual available recovery, not an idealized perfect type reconstruction.

## 4. The important trap: compiling is not correctness

The round-trip attempt was deliberately bounded and documented. It supplied Ghidra's integer typedefs, recovered declarations/constants, and lowered the two vector interleave operations needed by jsmn. It did **not** silently rewrite algorithms or repair reconstructed stack layouts. The reconstructed code and compatibility layer target the x86-64/LP64 ABI; they are not portable ISO C replacements.

Native QOI and SHA output still needed more extensive reconstruction than this normalizer supported. Generic x86-64 SHA output did compile—but produced the wrong hash even for the empty input. UBSan then diagnosed an **out-of-bounds access to an artificial nine-element stack array**. The emitted C had lost the relationship between pieces of the original stack storage.

The JSON parser was more subtle. It compiled and survived thousands of differential tests before this failure was found:

```text
Input bytes as text: "\u!000"
Original parser:     -2  (invalid input)
Recompiled output:    1  (accepted one string token)
```

The `!` is not a hexadecimal digit. This is an actual change in observable behavior, not a formatting complaint or a difference in unused memory.

The emitted range check included:

```c
0x25 < bVar3 - 0x41
```

Here `bVar3` is an unsigned byte. In C, it is promoted to `int` before subtraction. For `!`, the difference is negative, so the comparison fails to reject it. A subsequent masked bit test can then accept the character. The original machine code used an unsigned comparison.

The explicit repair was:

```c
0x25 < (uint)(bVar3 - 0x41)
```

Four such unsigned-cast repairs were needed in each of the `-O3` and `-Oz` parser outputs, at their respective range checks. **These are human-directed semantic repairs, not part of an automatic success.** The exact diffs are included.

Across six input build configurations, the bounded normalizer produced six compilable library outputs. Recompiling each at both `-O3` and `-Oz` gave **12 candidates; all 12 failed the differential tests**. This describes this extraction/normalization pipeline, not a claim that every possible Ghidra-assisted reconstruction must fail.

### How much testing was done?

Every original build passed:

* **12,000 JSON cases / 17,354 parse calls:** valid, malformed, truncated and incremental input, limited token buffers, and count-only mode. Return values, parser state, and token memory were compared against the `-O0` implementation.
* **500 QOI image cases / 1,500 decodes:** flat colors, noise, gradients, palettes and small color changes; RGB/RGBA conversion; exact original pixels and an independent Python QOI decoder.
* **1,200 SHA cases:** known vectors, padding boundaries, and randomized streaming chunks, compared with Python's `hashlib`.

Each of the four repaired parser/build combinations then passed the original suite **and 100,000 additional cases with a different seed**. Small ASan/UBSan probes passed for the repaired parsers. This is substantial testing, **not a proof of equivalence**.

[Regression examples](/assets/experiments/llvm-ghidra-2026/regressions.json) · [Correctness results](/assets/experiments/llvm-ghidra-2026/correctness.json) · [Held-out tests and sanitizer results](/assets/experiments/llvm-ghidra-2026/extra_checks.json)

## 5. Was anything faster or smaller after the round trip?

Only candidates that passed the tests were treated as usable performance comparisons. The repaired jsmn results were:

| Route | Function bytes | Parse time, median µs | Time interquartile range, µs |
| --- | ---: | ---: | ---: |
| Original → `-O2` | 1,479 | 5.931 | 5.609–6.073 |
| Original → `-O3` | 1,495 | 5.872 | 5.818–5.943 |
| Original → `-Oz` | 1,256 | 6.892 | 6.732–7.068 |
| `-O3` → Ghidra → **repair** → `-O3` | **1,468** | **5.725** | 5.550–5.797 |
| `-O3` → Ghidra → **repair** → `-Oz` | 1,513 | 7.943 | 7.901–9.061 |
| `-Oz` → Ghidra → **repair** → `-O3` | 1,631 | 6.107 | 6.048–6.344 |
| `-Oz` → Ghidra → **repair** → `-Oz` | 1,393 | 8.557 | 8.535–8.834 |

There is a genuine **small machine-code size win** in the best repaired route: **27 bytes, or 1.8%, smaller than the original `-O3` build**. It is just 11 bytes smaller than ordinary `-O2`. The original `-Oz` build remains substantially smaller than all repaired variants.

The repaired `-O3` route also measured **2.5% less time per parse** than the original `-O3` route. That is worth reporting, but not overselling. This is one input on one shared host with normal frequency scaling. Even the byte-identical `-O3` and explicit-unroll controls had medians differing by about 1.1%. The result does not establish a broad performance advantage.

For context, the much larger speedups came from **LLVM alone**, without any decompilation:

| Workload | Original `-O0` | Original `-O3` | Original `-Oz` |
| --- | ---: | ---: | ---: |
| Parse 4,782-byte JSON response | 20.655 µs | 5.872 µs | 6.892 µs |
| Encode 512×512 RGBA image | 3.109 ms | 1.198 ms | 1.312 ms |
| Decode that QOI image | 1.967 ms | 0.847 ms | 0.883 ms |
| Hash 1 MiB | 10.155 ms | 3.842 ms | 8.570 ms |

### Timing method

The JSON input was an actual GitHub release API response. The image was a **synthetic mixed-entropy workload**, combining flat, gradient, palette, and noisy regions. The hash input was a 1 MiB source-code corpus. These are real implementations, but not a representative survey of every application's data.

Timing used a C loop and `CLOCK_MONOTONIC`, with **11 randomized-order samples per combination**, approximately 180 ms per sample, pinned to logical CPU 2. File I/O, process launch, and dynamic loading were outside the timed region. QOI allocation/free was included; preparing the compressed input for the decoder was not.

[All timing samples](/assets/experiments/llvm-ghidra-2026/benchmark_raw.json) · [Medians and spread](/assets/experiments/llvm-ghidra-2026/benchmark_summary.json)

## 6. Verdict

**As an automatic way to improve maintainable source: no convincing success here.** Every whole-library decompilation was longer by the main source metric. Optimized abstractions became offsets, temporaries, expanded loops, machine operations, and less structured control flow. Compilable output could still be wrong.

**As a way to occasionally perturb the compiler into slightly different machine code: a qualified yes.** The repaired parser produced a tiny size reduction and a small measured timing improvement. But the useful candidate required semantic intervention, remained much worse source to maintain, and did not beat the compiler's normal size-oriented build on size.

**As an inspection tool: useful.** Decompilation made inlining, widened stores, unrolling, and SIMD lowering visible. That can suggest changes to investigate in the original source. It is a much stronger role than treating the recovered C as a trustworthy replacement for it.

This does not rule out better results from other decompilers, richer type recovery, different programs, PGO, or a purpose-built verified translator. It does show why “optimize hard, then decompile” is not by itself a reliable source transformation.

## Reproduce it

The [experiment archive](/assets/experiments/llvm-ghidra-2026/experiment.tar.gz) contains the scripts and observed outputs. Install the recorded Clang/LLVM and Ghidra versions, then:

```sh
export GHIDRA_HOME=/path/to/ghidra_12.1.4_PUBLIC
export JAVA_HOME=/path/to/jdk-21
export BENCH_CPU=2
bash scripts/reproduce.sh
```

The bundle includes original-source licenses and attribution, the minimal failing inputs, all semantic repair diffs, and raw decompiler output separately from modified output. CPU-dependent results will change on other machines.

**Primary references:** [Clang optimization options](https://clang.llvm.org/docs/CommandGuide/clang.html), [LLVM link-time optimization](https://llvm.org/docs/LinkTimeOptimization.html), [Ghidra release used](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.4_build), [Ghidra decompiler API](https://ghidra.re/ghidra_docs/api/ghidra/app/decompiler/DecompInterface.html). Full upstream revisions and tool versions are in the archive.

<p class="small">This is an agent-run experiment, not a literature review or a formal verification result. Measurements and unsuccessful round trips are preserved so the conclusions can be checked.</p>

</article>
