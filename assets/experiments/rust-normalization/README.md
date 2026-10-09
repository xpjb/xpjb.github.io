# Rust normalization measurements

Only derived metrics, source paths/hashes, trees and measurement tooling are published.
Selected excerpts are shown in the article. Full application source trees and private compiler logs are not included.

`measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT TAU2_INPUT TAU2_OUTPUT OUTPUT_DIR`
reproduces size metrics without editing those snapshots. It requires Python 3,
Tokei 12.1.2, and managed Cargo at `/usr/local/bin/cargo`, plus the locked Rust
meter dependencies cached for its offline build. Do not run Clippy or Cargo's
built-in test runner. Output includes all cfg branches and inactive test items.

The publication's metrics.json adds the previously executed validation results,
source preservation checks, and report hashes to the size measurements. Its
public test results describe only active migrated tests, not the original suite.

The original metrics/trees/phase analysis describe the initial emitter. The
`import-fix-metrics.json`, `import-fix-files.csv`, and `*-import-fix-tree.txt`
files separately describe the repaired emitter; initial results are retained.
The repaired normalizer has the same accepted inline/dead-removal sets and
suspended item counts. The verbose retry-helper frame remains unfixed.

To reproduce the import repair comparison from four generated output snapshots:

    /usr/local/bin/cargo build --locked --offline --manifest-path meter/Cargo.toml --bin anatomy
    python3 measure-import-fix.py COMPENDIUM_INITIAL COMPENDIUM_IMPORT_FIX TAU2_INITIAL TAU2_IMPORT_FIX OUTPUT_JSON --meter meter/target/debug/anatomy

The Python comparison only reads the supplied snapshots and the already-built
meter. Its output includes per-file hashes, syntax counts, normalization-report
hashes, and exact accepted rewrite-set comparisons. Validation results are added
separately from the actual compiler/test/differential runs.
