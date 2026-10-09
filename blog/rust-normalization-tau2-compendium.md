---
layout: experiment
title: "Rust normalization: Compendium and Tau2"
description: "Retained source measurements and the current test-migration blocker, without a false correctness claim."
permalink: /blog/rust-normalization-tau2-compendium/
---
<link rel="stylesheet" href="/assets/css/rust-normalization.css">
<article class="experiment-report normalization-report" markdown="1">

[← Writings](/writings.html)

# Rust normalization: Compendium and Tau2

**Current status: regeneration is blocked at public-test migration in both projects.** The hardened tool rejects unresolved test symbols/imports instead of silently suspending them. No replacement outputs were published.

The measurements below describe the retained generated snapshots, not successful output from the current tool.

## Retained snapshot sizes

| Measure | Compendium: original → generated | Tau2: original → generated |
|---|---:|---:|
| Rust source files | 80 → 7 | 210 → 18 |
| Physical lines | 60,269 → 67,365 (+11.8%) | 46,284 → 91,587 (+97.9%) |
| Same-formatter lines | 58,457 → 67,358 (+15.2%) | 79,884 → 91,563 (+14.6%) |
| Lexical tokens | 411,167 → 463,345 (+12.7%) | 639,286 → 710,433 (+11.1%) |

**Still larger after identical formatting:** +15.2% / +14.6%. Fewer files is not less code. Counts include inactive configurations and suspended tests; the download specifies the source scope.

## Generated code

Before, at the retry call and its helper:

```rust
let retry_at = next_attempt(attempt_at, Instant::now());

fn next_attempt(started: Instant, failed: Instant) -> Instant {
    (started + MIN_CONNECT_INTERVAL).max(failed)
}
```

In the retained generated snapshot:

```rust
let retry_at = {
    let (started, failed) = (attempt_at, Instant::now());
    (started + MIN_CONNECT_INTERVAL).max(failed)
};
```

No closure, cast, synthetic arguments, or trait import. The tuple preserves evaluation order. The same lowering handles other safe expressions, constructors, matches and iterator chains; necessary control-flow and lifetime boundaries remain.

Accepted single-site inlinings: **448 Compendium / 70 Tau2**. Unsupported cases remain explicit exceptions.

## Validation and limits

- **12 normalizer tests passed**, plus compiler, rustdoc and formatting checks. Current project regeneration stops on `E0425` (Compendium) and `E0432` (Tau2); these errors are not waived.
- The retained snapshots passed host/all-target compiler checks and their active public suites: **83 Compendium passed, 2 skipped; 93 Tau2 passed, 0 skipped**. Public `Color` matched the original bit-for-bit over **65,556 RGBA samples**.
- **Those passes do not establish transformation correctness.** The older migration suspended errors too broadly: 313 / 655 test-module items, including helpers/imports—not that many tests. Correct test migration remains unresolved.
- **324 captured input source/configuration hashes** and both Java files are unchanged; original repositories remain clean. Android and excluded Windows targets were not built.

## Evidence

Both sides use the same locked parser/printer; token counts ignore whitespace. Runtime and binary size were not benchmarked.

[Metrics, provenance and validation (JSON)](/assets/experiments/rust-normalization/metrics.json) · [Per-file measurements (CSV)](/assets/experiments/rust-normalization/files.csv) · [Inlining inventory (CSV)](/assets/experiments/rust-normalization/inlining-inventory.csv) · [Reproduction tools](/assets/experiments/rust-normalization/measurement-tools.tar.gz)

<details markdown="1">
<summary>Full source trees, before and after</summary>

### Compendium — before

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

### Compendium — after

```text
compendium/
├── examples/
│   ├── markdown_preview.rs  [60 lines]
│   ├── perf_scenarios.rs  [1,369 lines]
│   └── render_smoke.rs  [337 lines]
└── src/
    ├── bin1.rs  [34 lines]
    ├── implementation.rs  [44,579 lines]
    ├── lib.rs  [7,273 lines]
    └── tests.rs  [13,713 lines]
```

### Tau2 — before

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

### Tau2 — after

```text
tau2/
└── crates/
    ├── block-store/
    │   └── src/
    │       ├── implementation.rs  [186 lines]
    │       ├── lib.rs  [914 lines]
    │       └── tests.rs  [639 lines]
    ├── code-viewer/
    │   ├── examples/
    │   │   └── index_size.rs  [83 lines]
    │   └── src/
    │       ├── implementation.rs  [916 lines]
    │       ├── lib.rs  [244 lines]
    │       └── tests.rs  [579 lines]
    ├── daemon/
    │   └── src/
    │       ├── bin1.rs  [102 lines]
    │       ├── implementation.rs  [10,842 lines]
    │       ├── lib.rs  [2,061 lines]
    │       └── tests.rs  [11,391 lines]
    ├── frontend/
    │   └── src/
    │       ├── bin1.rs  [40 lines]
    │       ├── implementation.rs  [31,520 lines]
    │       ├── lib.rs  [3,975 lines]
    │       └── tests.rs  [23,739 lines]
    └── net/
        └── src/
            ├── implementation.rs  [1,855 lines]
            ├── lib.rs  [1,184 lines]
            └── tests.rs  [1,317 lines]
```

</details>

</article>
