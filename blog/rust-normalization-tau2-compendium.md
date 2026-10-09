---
layout: experiment
title: "Why generated Rust got larger: Tau2 and Compendium"
description: "Measured before/after file trees, line counts, tokens, semantic inlining, test migration and limitations for two real Rust workspaces."
permalink: /blog/rust-normalization-tau2-compendium/
---
<link rel="stylesheet" href="/assets/css/rust-normalization.css">
<article class="experiment-report normalization-report" markdown="1">

[← Writings](/writings.html)

<p class="kicker">Compiler-checked source transformation · Two real workspaces</p>

# Why the generated Rust got larger

<p class="deck">The normalizer made both codebases longer. Here are the measurements, generated-code costs, accepted inlinings, and test losses—not a claim that fewer files makes the result better.</p>

> **The code-size result is worse.** Physical LOC increased **27.3% in Compendium** and **107.4% in Tau2**. Applying the same parser and formatter to both sides still gives increases of **31.2%** and **20.1%**. Neither output is exception-free, and incompatible tests remain inactive rather than being counted as passing.

<div class="normalization-cards" markdown="0">
<div><span>Compendium physical LOC</span><strong>+27.3%</strong><small>+31.2% with identical formatting</small></div>
<div><span>Tau2 physical LOC</span><strong>+107.4%</strong><small>+20.1% with identical formatting</small></div>
<div><span>Single-site inlinings</span><strong>407 / 62</strong><small>Compendium / Tau2 · all tracked</small></div>
<div><span>Inactive test items</span><strong>968</strong><small>Imports/helpers/functions, not a test count</small></div>
</div>

**Read:** [scope](#scope) · [size](#size) · [phase costs](#costs) · [actual code](#code) · [inlinings](#inlinings) · [trees](#trees) · [packages](#packages) · [tests](#tests) · [validation](#validation) · [methodology and downloads](#methodology)

<h2 id="scope">1. What was transformed</h2>

The normalizer operated on a **new copy** of each input, not the original working trees. Tau2 here means the five-member `tau2-integration` workspace: `taud`, `tau-block-store`, `tau-net`, `tau-code-viewer`, and `tau-frontend`. Compendium is one package.

The requested per-package shape was:

```text
src/
├── lib.rs             public interfaces; public free functions may keep bodies
├── implementation.rs  private code and trait implementations
├── bin1.rs            one file per binary; original Cargo binary name retained
└── tests.rs           one external, public-interface integration-test target
```

Public inherent methods were moved into public `ThingBehaviour` traits where supported. Private functions with **exactly one resolved call site** were recursively inlined. Three calls from the same caller are still three sites: Compendium's `srgb_to_linear` correctly remains defined with its three calls. Cycles are allowed; dependency ordering is best effort.

**Scope of the size tables:** all Rust target-source files under the member packages' `src`, `tests`, `examples`, and `benches` directories, including inactive configurations and suspended tests. The counts match the normalizer's loaded-source inventory: **80 Compendium files and 210 Tau2 files**. Build scripts, excluded Windows crates, Java, assets, manifests, generated audit reports, and build caches are outside these size totals. Examples remain separate Cargo targets and are included in the counts.

<h2 id="size">2. Did LOC go down? No.</h2>

### Compendium

| Metric | Before | After | Change |
|---|---:|---:|---:|
| Rust target-source files | 80 | 7 | **-91.3%** |
| Physical lines (comments + blank lines included) | 60,269 | 76,716 | **+27.3%** |
| Same-parser / same-formatter lines | 58,457 | 76,709 | **+31.2%** |
| Lexical tokens | 411,167 | 547,344 | **+33.1%** |
| UTF-8 source bytes | 2,154,082 | 3,530,167 | **+63.9%** |

### Tau2

| Metric | Before | After | Change |
|---|---:|---:|---:|
| Rust target-source files | 210 | 18 | **-91.4%** |
| Physical lines (comments + blank lines included) | 46,284 | 95,996 | **+107.4%** |
| Same-parser / same-formatter lines | 79,884 | 95,972 | **+20.1%** |
| Lexical tokens | 639,286 | 748,812 | **+17.1%** |
| UTF-8 source bytes | 2,505,100 | 4,060,135 | **+62.1%** |

**File count is not code volume.** Tau2's original style packs substantial Rust onto single lines, so expanded formatting explains a large part of its physical-LOC increase. The format-controlled comparison and lexical-token count show that the increase is **not merely formatting**.

The transformation also introduces trait declarations alongside implementations, imports and module scaffolding, explicit type/UFCS paths, and typed call frames that preserve argument evaluation, ownership, early returns, and async capture. Namespaces are retained inside the coalesced files. These are real source costs. The measurements do not attribute an exact number of added lines to each mechanism, and do not establish faster runtime, smaller binaries, or lower cognitive complexity.

A concrete trade-off: Compendium's `implementation.rs` is now **53,068 lines**; Tau2 frontend's is **33,446 lines**. Fewer physical files does not automatically mean easier navigation.

<h2 id="costs">3. Where the extra code actually comes from</h2>

This section is a phase-by-phase measurement, not a guess based on the final file count. An isolated, hash-checked copy of the normalizer was instrumented to save its generated files after layout and after test suspension, then stop before inlining. The final column uses the already validated output. Trait inventories and suspension counts match; test files match except for three inactive imports of helpers subsequently deleted by the inliner. The original inputs, tool sources, and final outputs were not edited for this replay.

### Tau2: most growth occurs before inlining

| Stage | Format-controlled lines | Added lines | Tokens | Added tokens |
|---|---:|---:|---:|---:|
| Original, rendered by the same parser/formatter | 79,884 | — | 639,286 | — |
| Generated layout + initial external-test relocation | 93,619 | +13,735 | 728,562 | +89,276 |
| After incompatible-test suspension | 94,274 | +655 | 734,457 | +5,895 |
| After inlining, cleanup and ordering | 95,972 | +1,698 | 748,812 | +14,355 |

Of Tau2's **16,088 additional format-controlled lines**, **13,735 (85.4%)** appear in the layout/test-relocation phase. Only **1,698** appear in the later inlining/cleanup/ordering phase. The 62 accepted inlinings therefore do not explain the 107% headline by themselves.

Here is the exact reconciliation of that physical-LOC increase:

```text
46,284  original physical lines
+33,600  original-source parser/formatting-control difference
+13,735  generated layout and initial test relocation
   +655  always-false cfg attributes on incompatible test items
 +1,698  inlining, cleanup and dependency-ordering stage
    +24  final physical-vs-control formatting difference
-------
95,996  final physical lines
```

The first adjustment is a **parser/formatting control**, including ordinary-comment removal, not a claim that every extra raw line is merely whitespace. Even after that control, the generated program is larger.

### Compendium: the inlining stage itself is expensive

| Stage | Format-controlled lines | Added lines | Tokens | Added tokens |
|---|---:|---:|---:|---:|
| Original, rendered by the same parser/formatter | 58,457 | — | 411,167 | — |
| Generated layout + initial external-test relocation | 65,667 | +7,210 | 454,705 | +43,538 |
| After incompatible-test suspension | 65,980 | +313 | 457,522 | +2,817 |
| After inlining, cleanup and ordering | 76,709 | +10,729 | 547,344 | +89,822 |

The later stage adds **10,729 format-controlled lines and 89,822 tokens net**, despite removing 407 one-site helper definitions and three dead functions. This phase also includes obsolete-import cleanup and dependency ordering; it is not an independently timed or isolated optimizer benchmark. It is nevertheless clear that this emitter's accepted rewrites are not source-size wins in aggregate.

### The import and interface scaffolding is measurable

| Syntax in the measured files | Compendium before → after | Tau2 before → after |
|---|---:|---:|
| Import statements (`use`) | 445 → 2,156 | 982 → 4,186 |
| Tokens inside import statements, including attributes | 4,665 → 35,931 | 12,248 → 73,626 |
| Generated behaviour-trait declarations | 0 → 73 | 0 → 129 |
| Tokens in those trait declarations | 0 → 10,357 | 0 → 13,704 |
| Module declarations / wrappers | 96 → 172 | 195 → 312 |
| Empty implementation blocks | 4 → 14 | 6 → 10 |
| Parameterized generated closure frames | 0 → 394 | 0 → 58 |

The generated-closure count recognizes fresh `__inline_…` parameters. It excludes zero-argument frames and small typed blocks; it is a syntax count, not another inlining count.

**Tau2's layout phase alone adds 3,153 import statements.** Compendium's adds 1,377. Many carry their own `#[allow(unused_imports)]` attribute, and some add a `#[cfg(test)]` line. Existing imports are copied into split scopes; behaviour-trait imports and explicit facade/declaration reexports are also injected. This is a major, concrete source of bloat—not a consequence of moving a function to a different filename.

| Added token category in layout / initial test relocation | Compendium | Tau2 |
|---|---:|---:|
| Import statements, including their visibility/attributes | +25,613 | +58,801 |
| Generated behaviour-trait declarations | +10,357 | +13,704 |
| Module wrappers, excluding their contents | +1,317 | +3,217 |
| Remaining syntax | +6,251 | +13,554 |
| **Total layout token increase** | **+43,538** | **+89,276** |

These token categories do not overlap: complete `use` items, complete generated trait declarations, module wrappers with their bodies excluded, and everything remaining. The final row is a reconciliation, not an attribution of every remaining token to one mechanism. Trait interfaces intentionally add a second declaration of each moved method's signature; that requested shape has a size cost. It does not justify indiscriminate imports or unnecessarily verbose call frames.

<h2 id="code">4. What the generated code looks like</h2>

### A three-line helper becomes a 19-line call-site frame

This is the actual Tau2 retry-time helper and its one call site. These excerpts omit surrounding functions and imports, but are not invented examples.

**Before — helper plus call site (four source lines):**

```rust
fn next_attempt(started: Instant, failed: Instant) -> Instant {
    (started + MIN_CONNECT_INTERVAL).max(failed)
}

// At its call site:
let retry_at = next_attempt(attempt_at, Instant::now());
```

**After — the helper is removed, but the call site is now:**

```rust
let retry_at = ({
    #[allow(unused_imports)]
    use Ord as _;
    (|
        __inline_0_argument_0: ::std::time::Instant,
        __inline_0_argument_1: ::std::time::Instant,
    | -> ::std::time::Instant {
        let started = __inline_0_argument_0;
        let failed = __inline_0_argument_1;
        <::std::time::Instant as Ord>::max(
            (started + crate::net::health::MIN_CONNECT_INTERVAL),
            failed,
        )
    })
        as fn(
            ::std::time::Instant,
            ::std::time::Instant,
        ) -> ::std::time::Instant
})(attempt_at, Instant::now());
```

The extra code consists of typed closure parameters, fresh-name rebinding, explicit UFCS dispatch, a repeated function-pointer signature/cast, and the call wrapper. General call frames are intended to preserve argument evaluation, drops, returns, and async behavior. **This particular helper has no `return`, `?`, or async body.** Its expansion reflects the emitter's conservative full-frame choice, not evidence that a 19-line expression is intrinsically necessary here.

Inlining is not automatically simplification. Removing a helper name while replacing its call with this much machinery can make the source harder to read, even when the compiler accepts it.

### Trait/import scaffolding is copied around the modules

For another concrete example, the original Tau2 `cache_ttl.rs` starts with two `use` statements. Its corresponding implementation module now starts with this block:

```rust
#[allow(unused_imports)]
use tau_block_store::__unsloppifier_traits::*;
#[allow(unused_imports)]
use tau_code_viewer::__unsloppifier_traits::*;
#[allow(unused_imports)]
use tau_net::__unsloppifier_traits::*;
#[cfg(test)]
#[allow(unused_imports)]
use taud::__unsloppifier_traits::*;
#[allow(unused_imports)]
use crate::__unsloppifier_traits::*;
#[allow(unused_imports)]
pub(crate) use crate::cache_ttl::EstimateBehaviour;
#[allow(unused_imports)]
pub(crate) use crate::cache_ttl::Estimate;
#[allow(unused_imports)]
pub(crate) use crate::cache_ttl::*;
use crate::{clock, feed::Feed, tooltip::{Content, ACCENT, INK, WARNING}};
use tau_net::{EventKind, EventRole, SessionStatus, SessionSummary};
```

Those trait-prelude imports and explicit facade imports are generated scaffolding. The same general pattern recurs across mirrored API/implementation scopes and migrated test scopes. The file also retains an empty `impl Basis {}` after its sole method was inlined. Both are visible cleanup/selection problems; a reduced physical file count does not resolve them.

The next improvements should be measured against these costs: narrower imports, smaller call-site rewrites where justified, less repeated qualification, and removal of empty leftovers where safe. The existing output is not evidence those improvements have already been made.

<h2 id="inlinings">5. Yes, the inlinings were tracked</h2>

These counts come from the accepted-rewrite records, not inferred differences in function names or file counts:

| Package | Accepted inlinings | Dead removals |
|---|---:|---:|
| `compendium` | 407 | 3 |
| `taud` | 7 | 0 |
| `tau-block-store` | 1 | 0 |
| `tau-net` | 0 | 0 |
| `tau-code-viewer` | 0 | 0 |
| `tau-frontend` | 54 | 2 |
| **Total** | **469** | **5** |

[Download every accepted inlining and dead removal (CSV)](/assets/experiments/rust-normalization/inlining-inventory.csv), or [the per-package JSON inventory](/assets/experiments/rust-normalization/inlining-inventory.json). Names refer to the normalized module/function identities recorded by the transformer. Retained candidates are separate: **288 Compendium and 126 Tau2 inlining exceptions**. None is included in the accepted count.

The changes preserve the exact-single-site policy: `srgb_to_linear` remains because its one caller contains three calls. The full inventories distinguish real accepted rewrites from functions intentionally retained.

<h2 id="trees">6. Before and after file trees</h2>

These are complete **in-scope Rust source trees**, not sketches. Each leaf shows its physical line count. Expand the “before” trees to inspect every original file. Cargo/configuration files and preserved platform support are described separately below, rather than mixed into the Rust file-reduction figures.

### Compendium

<details markdown="1">
<summary>Before — 80 Rust target-source files (expand full tree)</summary>

```text
compendium/
├── examples/
│   ├── markdown_preview.rs  [24 lines]
│   ├── perf_scenarios.rs  [1,334 lines]
│   └── render_smoke.rs  [322 lines]
├── src/
│   ├── agent/
│   │   ├── codex.rs  [427 lines]
│   │   ├── codex_auth.rs  [535 lines]
│   │   ├── image.rs  [196 lines]
│   │   └── mod.rs  [701 lines]
│   ├── app/
│   │   ├── pane/
│   │   │   ├── editing.rs  [1,204 lines]
│   │   │   ├── library.rs  [415 lines]
│   │   │   ├── mod.rs  [28 lines]
│   │   │   ├── prediction.rs  [266 lines]
│   │   │   ├── render.rs  [728 lines]
│   │   │   ├── scrollbar.rs  [158 lines]
│   │   │   └── streaming.rs  [997 lines]
│   │   ├── chrome.rs  [925 lines]
│   │   ├── confirm_modal.rs  [202 lines]
│   │   ├── event_loop.rs  [704 lines]
│   │   ├── input.rs  [898 lines]
│   │   ├── mod.rs  [188 lines]
│   │   ├── persistence.rs  [1,923 lines]
│   │   ├── picker.rs  [361 lines]
│   │   ├── popup.rs  [124 lines]
│   │   ├── preview.rs  [330 lines]
│   │   ├── render.rs  [67 lines]
│   │   ├── sync.rs  [2,930 lines]
│   │   ├── tests.rs  [3,743 lines]
│   │   ├── text_prompt.rs  [182 lines]
│   │   └── workspace.rs  [314 lines]
│   ├── document/
│   │   ├── compat/
│   │   │   ├── mod.rs  [84 lines]
│   │   │   ├── store_v4.rs  [821 lines]
│   │   │   ├── v1.rs  [1,074 lines]
│   │   │   └── v2.rs  [169 lines]
│   │   ├── arena.rs  [256 lines]
│   │   ├── edit.rs  [740 lines]
│   │   ├── hash.rs  [47 lines]
│   │   ├── history.rs  [106 lines]
│   │   ├── merge.rs  [1,467 lines]
│   │   ├── node_index.rs  [453 lines]
│   │   ├── paint.rs  [426 lines]
│   │   ├── persistence.rs  [500 lines]
│   │   ├── render.rs  [361 lines]
│   │   ├── resource_walk.rs  [125 lines]
│   │   ├── root.rs  [839 lines]
│   │   ├── rope.rs  [1,452 lines]
│   │   ├── sqlite.rs  [484 lines]
│   │   ├── storage.rs  [102 lines]
│   │   ├── store.rs  [6,002 lines]
│   │   ├── text_view.rs  [240 lines]
│   │   └── tree_chunks.rs  [27 lines]
│   ├── sync/
│   │   ├── discovery.rs  [290 lines]
│   │   ├── hub.rs  [526 lines]
│   │   ├── identity.rs  [839 lines]
│   │   ├── mod.rs  [48 lines]
│   │   ├── session.rs  [1,315 lines]
│   │   ├── trace.rs  [146 lines]
│   │   └── wire.rs  [963 lines]
│   ├── widgets/
│   │   ├── arrow.rs  [329 lines]
│   │   ├── command_runner.rs  [71 lines]
│   │   ├── mod.rs  [149 lines]
│   │   └── trivial.rs  [62 lines]
│   ├── base64.rs  [133 lines]
│   ├── camera.rs  [88 lines]
│   ├── control.rs  [2,033 lines]
│   ├── document.rs  [4,796 lines]
│   ├── fs_import.rs  [393 lines]
│   ├── geometry.rs  [149 lines]
│   ├── lib.rs  [32 lines]
│   ├── logging.rs  [114 lines]
│   ├── main.rs  [30 lines]
│   ├── markdown.rs  [372 lines]
│   ├── presentation.rs  [137 lines]
│   ├── renderer.rs  [3,446 lines]
│   ├── settings.rs  [1,507 lines]
│   ├── style.rs  [153 lines]
│   ├── text_editor.rs  [1,359 lines]
│   ├── types.rs  [2,665 lines]
│   └── world.rs  [1,283 lines]
└── tests/
    ├── save_regressions.rs  [77 lines]
    ├── sync_hub_workflow.rs  [478 lines]
    └── text_integration.rs  [285 lines]
```

</details>

<details markdown="1" open>
<summary>After — 7 Rust target-source files</summary>

```text
compendium/
├── examples/
│   ├── markdown_preview.rs  [56 lines]
│   ├── perf_scenarios.rs  [1,539 lines]
│   └── render_smoke.rs  [347 lines]
└── src/
    ├── bin1.rs  [30 lines]
    ├── implementation.rs  [53,068 lines]
    ├── lib.rs  [7,967 lines]
    └── tests.rs  [13,709 lines]
```

</details>
### Tau2 workspace

<details markdown="1">
<summary>Before — 210 Rust target-source files (expand full tree)</summary>

```text
tau2/
└── crates/
    ├── block-store/
    │   ├── src/
    │   │   └── lib.rs  [539 lines]
    │   └── tests/
    │       └── unit/
    │           └── core.rs  [310 lines]
    ├── code-viewer/
    │   ├── examples/
    │   │   └── index_size.rs  [48 lines]
    │   ├── src/
    │   │   ├── filesystem.rs  [189 lines]
    │   │   ├── finder.rs  [158 lines]
    │   │   ├── lib.rs  [92 lines]
    │   │   └── syntax.rs  [56 lines]
    │   └── tests/
    │       └── unit/
    │           ├── core.rs  [24 lines]
    │           ├── filesystem.rs  [127 lines]
    │           ├── finder.rs  [28 lines]
    │           ├── finder_matcher.rs  [20 lines]
    │           └── syntax.rs  [7 lines]
    ├── daemon/
    │   ├── src/
    │   │   ├── agent/
    │   │   │   ├── provider/
    │   │   │   │   ├── codex.rs  [240 lines]
    │   │   │   │   ├── completions.rs  [159 lines]
    │   │   │   │   ├── mod.rs  [437 lines]
    │   │   │   │   └── recovery.rs  [90 lines]
    │   │   │   ├── auth.rs  [213 lines]
    │   │   │   ├── auth_lock.rs  [92 lines]
    │   │   │   ├── history.rs  [183 lines]
    │   │   │   ├── mod.rs  [534 lines]
    │   │   │   └── tools.rs  [190 lines]
    │   │   ├── net/
    │   │   │   └── mod.rs  [695 lines]
    │   │   ├── attachments.rs  [370 lines]
    │   │   ├── catalog.rs  [208 lines]
    │   │   ├── config.rs  [94 lines]
    │   │   ├── lib.rs  [86 lines]
    │   │   ├── main.rs  [53 lines]
    │   │   ├── maintenance.rs  [39 lines]
    │   │   ├── manager.rs  [557 lines]
    │   │   ├── projection.rs  [220 lines]
    │   │   ├── projects.rs  [155 lines]
    │   │   ├── settings.rs  [212 lines]
    │   │   ├── state.rs  [723 lines]
    │   │   ├── transcript.rs  [258 lines]
    │   │   └── usage.rs  [112 lines]
    │   └── tests/
    │       ├── support/
    │       │   └── mod.rs  [123 lines]
    │       ├── unit/
    │       │   ├── agent/
    │       │   │   ├── provider/
    │       │   │   │   ├── codex.rs  [50 lines]
    │       │   │   │   └── recovery.rs  [41 lines]
    │       │   │   ├── activity.rs  [134 lines]
    │       │   │   ├── auth.rs  [16 lines]
    │       │   │   ├── auth_lock.rs  [40 lines]
    │       │   │   ├── compaction.rs  [165 lines]
    │       │   │   ├── control.rs  [422 lines]
    │       │   │   ├── device_login.rs  [68 lines]
    │       │   │   ├── history.rs  [12 lines]
    │       │   │   ├── mod.rs  [1,249 lines]
    │       │   │   ├── models.rs  [96 lines]
    │       │   │   ├── provider.rs  [49 lines]
    │       │   │   ├── recovery.rs  [360 lines]
    │       │   │   ├── safety.rs  [128 lines]
    │       │   │   ├── shared_refresh.rs  [39 lines]
    │       │   │   ├── thinking.rs  [55 lines]
    │       │   │   └── tools.rs  [209 lines]
    │       │   ├── attachments.rs  [9 lines]
    │       │   ├── blocks.rs  [93 lines]
    │       │   ├── catalog.rs  [84 lines]
    │       │   ├── maintenance.rs  [12 lines]
    │       │   ├── operations.rs  [16 lines]
    │       │   ├── projects.rs  [35 lines]
    │       │   ├── protocol_audit.rs  [29 lines]
    │       │   ├── server.rs  [333 lines]
    │       │   ├── state_reads.rs  [58 lines]
    │       │   ├── transcript.rs  [70 lines]
    │       │   └── usage.rs  [96 lines]
    │       └── sqlite_crash.rs  [121 lines]
    ├── frontend/
    │   ├── src/
    │   │   ├── app/
    │   │   │   ├── code_view/
    │   │   │   │   └── paint.rs  [148 lines]
    │   │   │   ├── ui/
    │   │   │   │   ├── transcript/
    │   │   │   │   │   └── cache.rs  [40 lines]
    │   │   │   │   ├── attachments.rs  [631 lines]
    │   │   │   │   ├── codex_login.rs  [164 lines]
    │   │   │   │   ├── composer.rs  [564 lines]
    │   │   │   │   ├── controls.rs  [708 lines]
    │   │   │   │   ├── dialogs.rs  [834 lines]
    │   │   │   │   ├── header.rs  [226 lines]
    │   │   │   │   ├── menu.rs  [437 lines]
    │   │   │   │   ├── message_row.rs  [430 lines]
    │   │   │   │   ├── mod.rs  [553 lines]
    │   │   │   │   ├── notice.rs  [139 lines]
    │   │   │   │   ├── operations.rs  [322 lines]
    │   │   │   │   ├── scroll.rs  [236 lines]
    │   │   │   │   ├── settings.rs  [547 lines]
    │   │   │   │   ├── sidebar.rs  [430 lines]
    │   │   │   │   ├── timers.rs  [115 lines]
    │   │   │   │   ├── tooltips.rs  [119 lines]
    │   │   │   │   ├── transcript.rs  [670 lines]
    │   │   │   │   ├── viewer.rs  [211 lines]
    │   │   │   │   └── workspace.rs  [444 lines]
    │   │   │   ├── attachments.rs  [363 lines]
    │   │   │   ├── code_view.rs  [1,480 lines]
    │   │   │   ├── mobile_input.rs  [51 lines]
    │   │   │   ├── notices.rs  [36 lines]
    │   │   │   ├── ripple.rs  [61 lines]
    │   │   │   └── ui_owner.rs  [243 lines]
    │   │   ├── desktop/
    │   │   │   ├── scroll.rs  [28 lines]
    │   │   │   └── wake.rs  [38 lines]
    │   │   ├── editor/
    │   │   │   ├── mobile.rs  [69 lines]
    │   │   │   └── touch.rs  [79 lines]
    │   │   ├── net/
    │   │   │   ├── files.rs  [141 lines]
    │   │   │   ├── health.rs  [250 lines]
    │   │   │   ├── mailbox.rs  [79 lines]
    │   │   │   ├── mod.rs  [513 lines]
    │   │   │   ├── sync.rs  [235 lines]
    │   │   │   └── transfers.rs  [211 lines]
    │   │   ├── render/
    │   │   │   └── trace.rs  [262 lines]
    │   │   ├── android.rs  [431 lines]
    │   │   ├── app.rs  [558 lines]
    │   │   ├── cache_ttl.rs  [97 lines]
    │   │   ├── clock.rs  [29 lines]
    │   │   ├── codex_usage.rs  [85 lines]
    │   │   ├── controller.rs  [1,819 lines]
    │   │   ├── daemon_settings.rs  [280 lines]
    │   │   ├── demo.rs  [90 lines]
    │   │   ├── desktop.rs  [490 lines]
    │   │   ├── disk.rs  [70 lines]
    │   │   ├── downloads.rs  [257 lines]
    │   │   ├── editor.rs  [646 lines]
    │   │   ├── feed.rs  [239 lines]
    │   │   ├── fonts.rs  [248 lines]
    │   │   ├── icons.rs  [278 lines]
    │   │   ├── keyboard.rs  [43 lines]
    │   │   ├── lib.rs  [38 lines]
    │   │   ├── main.rs  [24 lines]
    │   │   ├── mobile_input.rs  [63 lines]
    │   │   ├── models.rs  [49 lines]
    │   │   ├── notice.rs  [37 lines]
    │   │   ├── render.rs  [1,015 lines]
    │   │   ├── replica.rs  [848 lines]
    │   │   ├── scroll.rs  [138 lines]
    │   │   ├── store.rs  [510 lines]
    │   │   └── tooltip.rs  [243 lines]
    │   └── tests/
    │       ├── support/
    │       │   ├── block_outage.rs  [203 lines]
    │       │   ├── native_trace.rs  [30 lines]
    │       │   ├── network_mailbox.rs  [26 lines]
    │       │   ├── pressure_link.rs  [143 lines]
    │       │   └── pressure_metrics.rs  [93 lines]
    │       ├── unit/
    │       │   ├── app/
    │       │   │   ├── ui/
    │       │   │   │   ├── attachments.rs  [210 lines]
    │       │   │   │   ├── codex_login.rs  [69 lines]
    │       │   │   │   ├── composer.rs  [26 lines]
    │       │   │   │   ├── controls.rs  [18 lines]
    │       │   │   │   ├── dialogs.rs  [263 lines]
    │       │   │   │   ├── lifetime.rs  [612 lines]
    │       │   │   │   ├── scroll.rs  [50 lines]
    │       │   │   │   └── transcript_cache.rs  [37 lines]
    │       │   │   ├── attachments.rs  [129 lines]
    │       │   │   ├── code_view.rs  [494 lines]
    │       │   │   ├── composer_status.rs  [32 lines]
    │       │   │   ├── connection.rs  [364 lines]
    │       │   │   ├── control.rs  [155 lines]
    │       │   │   ├── download_interaction.rs  [288 lines]
    │       │   │   ├── download_render.rs  [109 lines]
    │       │   │   ├── editor.rs  [206 lines]
    │       │   │   ├── mobile_input.rs  [367 lines]
    │       │   │   ├── navigation.rs  [316 lines]
    │       │   │   ├── notices.rs  [29 lines]
    │       │   │   ├── notices_render.rs  [53 lines]
    │       │   │   ├── project.rs  [234 lines]
    │       │   │   ├── repaint.rs  [218 lines]
    │       │   │   ├── ripple.rs  [33 lines]
    │       │   │   ├── startup.rs  [57 lines]
    │       │   │   ├── thinking.rs  [37 lines]
    │       │   │   ├── tooltip.rs  [169 lines]
    │       │   │   ├── transcript.rs  [189 lines]
    │       │   │   └── viewer.rs  [135 lines]
    │       │   ├── desktop/
    │       │   │   ├── scroll.rs  [26 lines]
    │       │   │   └── wake.rs  [37 lines]
    │       │   ├── editor/
    │       │   │   └── mobile.rs  [24 lines]
    │       │   ├── net/
    │       │   │   ├── sync/
    │       │   │   │   └── checkpoint.rs  [179 lines]
    │       │   │   ├── files.rs  [45 lines]
    │       │   │   ├── files_index.rs  [86 lines]
    │       │   │   ├── health.rs  [121 lines]
    │       │   │   ├── mailbox.rs  [67 lines]
    │       │   │   ├── sync.rs  [141 lines]
    │       │   │   └── transfers.rs  [102 lines]
    │       │   ├── render/
    │       │   │   ├── repaint.rs  [180 lines]
    │       │   │   └── trace.rs  [228 lines]
    │       │   ├── app_usage.rs  [23 lines]
    │       │   ├── cache_ttl.rs  [74 lines]
    │       │   ├── codex_usage.rs  [51 lines]
    │       │   ├── controller.rs  [163 lines]
    │       │   ├── controller_models.rs  [89 lines]
    │       │   ├── disk.rs  [11 lines]
    │       │   ├── downloads.rs  [163 lines]
    │       │   ├── editor.rs  [400 lines]
    │       │   ├── end_to_end.rs  [563 lines]
    │       │   ├── icons.rs  [25 lines]
    │       │   ├── mobile_input.rs  [9 lines]
    │       │   ├── net.rs  [9 lines]
    │       │   ├── render_tests.rs  [123 lines]
    │       │   ├── replica.rs  [837 lines]
    │       │   ├── scroll.rs  [126 lines]
    │       │   └── store.rs  [5 lines]
    │       ├── activity.rs  [310 lines]
    │       ├── connection_probe.rs  [269 lines]
    │       ├── model_catalog.rs  [103 lines]
    │       ├── native_link.rs  [101 lines]
    │       ├── network_pressure.rs  [352 lines]
    │       ├── recovery.rs  [586 lines]
    │       ├── remote_files.rs  [80 lines]
    │       ├── startup.rs  [147 lines]
    │       ├── thinking_level.rs  [33 lines]
    │       └── transcript_prefetch.rs  [182 lines]
    └── net/
        ├── src/
        │   ├── native/
        │   │   └── read.rs  [137 lines]
        │   ├── blocks.rs  [215 lines]
        │   ├── files.rs  [57 lines]
        │   ├── lib.rs  [483 lines]
        │   ├── native.rs  [658 lines]
        │   ├── settings.rs  [110 lines]
        │   └── transcript.rs  [132 lines]
        └── tests/
            ├── unit/
            │   └── native.rs  [22 lines]
            ├── contracts.rs  [30 lines]
            └── native.rs  [514 lines]
```

</details>

<details markdown="1" open>
<summary>After — 18 Rust target-source files</summary>

```text
tau2/
└── crates/
    ├── block-store/
    │   └── src/
    │       ├── implementation.rs  [253 lines]
    │       ├── lib.rs  [942 lines]
    │       └── tests.rs  [639 lines]
    ├── code-viewer/
    │   ├── examples/
    │   │   └── index_size.rs  [81 lines]
    │   └── src/
    │       ├── implementation.rs  [944 lines]
    │       ├── lib.rs  [250 lines]
    │       └── tests.rs  [587 lines]
    ├── daemon/
    │   └── src/
    │       ├── bin1.rs  [100 lines]
    │       ├── implementation.rs  [11,235 lines]
    │       ├── lib.rs  [2,201 lines]
    │       └── tests.rs  [11,589 lines]
    ├── frontend/
    │   └── src/
    │       ├── bin1.rs  [39 lines]
    │       ├── implementation.rs  [33,446 lines]
    │       ├── lib.rs  [4,651 lines]
    │       └── tests.rs  [24,397 lines]
    └── net/
        └── src/
            ├── implementation.rs  [2,093 lines]
            ├── lib.rs  [1,223 lines]
            └── tests.rs  [1,326 lines]
```

</details>


### Preserved outside those source totals

- **Compendium:** `build.rs`, the excluded `windows/` subtree, and non-Rust resources remain.
- **Tau2:** `crates/frontend/build.rs`, the excluded `crates/windows/` subtree, Android/platform support, and non-Rust resources remain.
- Both Java files—`crates/frontend/android/java/app/tau/rust/MainActivity.java` and `crates/frontend/tests/android/SelectionBridgeTest.java`—are **byte-for-byte unchanged**. Platform-specific Rust is retained in the coalesced sources; this is not an Android cross-build or runtime certification.
- Both build scripts and all ten excluded Windows Rust files are byte-for-byte unchanged.

**Preservation precision:** the old normalization summaries called the excluded Windows subtrees “untouched.” A byte comparison shows a narrower truth: their Rust files are unchanged, but **one Compendium and three Tau2 `Cargo.toml` files were reformatted**. Parsing the before/after TOML yields identical values. They are not claimed to have been normalized or compiled as workspace members.

<h2 id="packages">7. Per-package figures and transformations</h2>

| Package | Rust files | Physical LOC | Formatted LOC | Traits | Suspended test **items** | Public tests passed |
|---|---:|---:|---:|---:|---:|---:|
| `compendium` | 80 → 7 | 60,269 → 76,716 | 58,457 → 76,709 | 73 | 313 | 83 |
| `taud` | 53 → 4 | 10,132 → 25,125 | 21,645 → 25,115 | 19 | 181 | 2 |
| `tau-block-store` | 2 → 3 | 849 → 1,834 | 1,663 → 1,831 | 0 | 0 | 18 |
| `tau-net` | 10 → 3 | 2,358 → 4,642 | 3,817 → 4,639 | 21 | 3 | 23 |
| `tau-code-viewer` | 10 → 4 | 749 → 1,862 | 1,536 → 1,858 | 6 | 4 | 8 |
| `tau-frontend` | 135 → 4 | 32,196 → 62,533 | 51,223 → 62,529 | 83 | 467 | 42 |

Compendium's test result also has **2 skipped tests**. “Suspended items” includes imports and fixture helpers as well as functions; it is deliberately not labeled “tests removed.”

| Transformation | Compendium | Tau2 |
|---|---:|---:|
| Extracted public behaviour traits | 73 | 129 |
| Accepted single-site inlinings | 407 | 62 |
| Dead-function removals | 3 | 2 |
| Recorded retained-inlining exceptions | 288 | 126 |

An inlining exception is **not** a successful inlining. Retained cases include const/ABI contracts, opaque macro or generic contexts, unnameable types, lifetime/dispatch constraints, and compiler-rejected rewrites. Existing public trait defaults and some inherent methods remain where moving them would change the contract. File coalescing is implemented; full namespace elimination is not.

<h2 id="tests">8. Do incompatible tests necessarily test implementation rather than behavior?</h2>

**No. Visibility and the kind of assertion are separate questions.** A private helper can implement meaningful behavior; a public API can expose implementation details. The chosen rule—external tests may use only a crate's public API—is a boundary policy, not a proof that every rejected test was a bad test.

Two examples from the actual Compendium input illustrate the distinction:

- **`provider_serializers_encode_typed_image_parts_at_boundary`** checks image serialization into provider request payloads. That is meaningful protocol behavior. It fails migration because the serializer methods it calls are private. A public-boundary rewrite or an intentionally exposed component boundary would be needed; calling it “non-behavioral” would be misleading.
- **`forked_roots_share_node_refs_until_cow`** asserts exact node references and internal arena reference counts. Those assertions are representation-coupled (though they can still be valuable invariant tests). A black-box substitute could check that editing a fork preserves the original, but would not necessarily detect the same sharing or resource-management regressions.

The compiler reports also contain missing fixtures/imports, unavailable test-only methods, ambiguous names, type errors, and migration/cascade failures. We cannot responsibly assign all of these to “tests of implementation details.”

### What the recorded diagnostics actually say

| Recorded diagnostic category | Compendium items | Tau2 items |
|---|---:|---:|
| Explicit private / inaccessible API | 155 | 268 |
| Unresolved name or import; can include cascades | 156 | 339 |
| Unavailable method / associated item | 2 | 13 |
| Other compile incompatibility | 0 | 35 |
| **Total suspended items** | **313** | **655** |

These are **mutually exclusive message categories, not established root causes**. If an item's diagnostics explicitly mention privacy, it goes in the first row; unresolved names take precedence over missing-method and other messages. Removing an inaccessible helper can produce later “not found” errors in many dependent tests. Tau2's “other” row includes ambiguous imports, type-size errors, and call/future mismatches, some of which may themselves be cascades or migration defects.

The original syntax inventory found **314 test-function declarations in Compendium and 466 in Tau2**, across configurations. Those are not baseline execution counts, and **313 / 655 suspended items are not test-function counts**. No coverage percentage should be inferred by subtracting these unlike quantities.

**The loss of active coverage is real.** For example, the surviving Tau daemon public suite has only **2 tests**, despite 117 original test-function declarations in its source inventory. Passing the remaining suite is not equivalent to preserving the original suite. Tests should be reviewed and rewritten where appropriate—not dismissed or made to pass by publishing internals solely for test access.

<h2 id="validation">9. What was actually validated</h2>

- Both outputs passed Cargo compiler checks in staging **and again at their final published filesystem paths**, on the host/default configuration.
- The normalizer's **65 tests passed** under nextest; its all-target compiler check, rustdoc, and formatting checks passed. Clippy and Cargo's built-in test runner were not used.
- **Compendium: 83 active public-interface tests passed; 2 skipped.**
- **Tau2: 93 active public-interface tests passed; none skipped.** The per-package counts are in the table above.
- Original versus normalized Compendium public `Color` execution produced **bit-identical results for 65,556 RGBA samples: 262,224 float channels**. This is a numerical check of that API, not proof of the whole application's equivalence.
- Both original input repositories remain clean, and all **324 captured input source/configuration hashes** are unchanged.

Compiler success is not behavioral equivalence. The public test suites and differential fixtures provide bounded evidence, not a universal proof. Other feature combinations, Android execution, and excluded Windows targets were not certified. Runtime speed, binary size, and compilation-time improvements were not benchmarked.

<h2 id="methodology">10. Measurement method, provenance, and downloads</h2>

1. Enumerate the same member-package source directories on each side; do not omit inactive tests from the output's size.
2. Count physical lines and UTF-8 bytes directly from each file.
3. Parse each file with `syn` and render it with the **same locked `prettyplease` toolchain** on both sides. Count those lines as the format-controlled metric. Ordinary comments are removed by AST rendering; documentation attributes and all conditional source remain. This is a consistent formatting comparison, not a behavioral or semantic reduction metric.
4. Count lexical tokens recursively using `proc_macro2`: punctuation tokens and delimiters count individually; a literal counts once regardless of length. Ordinary comments are discarded by tokenization; documentation comments become attributes and remain counted. Whitespace changes do not drive this count.
5. Also record Tokei 12.1.2's code/comment/blank counts in the downloads. Embedded documentation is treated as comments. Its parser has small line-accounting discrepancies on six files (recorded as `counter_line_delta`); the headline physical counts are independently measured, not reconstructed from Tokei totals.
6. Record per-file hashes, source commits, normalization-report hashes, and a downloadable, locked measurement program. Selected application-code excerpts appear above; full application sources and private compiler logs are not published.

| Input | Source commit |
|---|---|
| Compendium | `7227df58674d905245672d0bcd7c78ae31ebcf73` |
| Tau2 integration snapshot | `a7ab255a87dbd4113d992f871a76a7e6716016e3` |

**Downloads**

- [Measured phase costs and syntax anatomy (JSON)](/assets/experiments/rust-normalization/phase-costs.json)
- [Audit-only normalizer instrumentation patch](/assets/experiments/rust-normalization/phase-instrumentation.patch)
- [Actual code excerpts used above (JSON)](/assets/experiments/rust-normalization/code-excerpts.json)
- [Accepted inlining inventory (CSV)](/assets/experiments/rust-normalization/inlining-inventory.csv) / [JSON](/assets/experiments/rust-normalization/inlining-inventory.json)


- [Complete derived metrics and validation summary (JSON)](/assets/experiments/rust-normalization/metrics.json)
- [Per-file measurements and hashes (CSV)](/assets/experiments/rust-normalization/files.csv)
- [Reproduction scripts and locked Rust meter (tar.gz)](/assets/experiments/rust-normalization/measurement-tools.tar.gz)
- Plain-text trees: [Compendium before](/assets/experiments/rust-normalization/compendium-before-tree.txt) / [after](/assets/experiments/rust-normalization/compendium-after-tree.txt), [Tau2 before](/assets/experiments/rust-normalization/tau2-before-tree.txt) / [after](/assets/experiments/rust-normalization/tau2-after-tree.txt)

To reproduce the size measurements with the four local source snapshots:

```sh
python3 measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT \
  TAU2_INPUT TAU2_OUTPUT RESULTS_DIRECTORY
```

The script uses `/usr/local/bin/cargo`, does not invoke Clippy or Cargo's built-in test runner, and does not edit the source snapshots. The locked meter uses `prettyplease 0.2.37` and `proc_macro2 1.0.107`; the complete dependency versions are in its `Cargo.lock`. The initial offline Cargo invocation requires those dependencies to be cached.

---

**Bottom line:** this version produces larger source and loses active test coverage. Compiler-accepted inlinings do not by themselves make its generated code concise or pleasant to read. A lower file count does not offset those failures.

</article>
