# Rust normalization measurements

Only derived metrics, source paths/hashes, trees and measurement tooling are published.
No application source or private compiler logs are included.

`measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT TAU2_INPUT TAU2_OUTPUT OUTPUT_DIR`
reproduces size metrics without editing those snapshots. It requires Python 3,
Tokei 12.1.2, and managed Cargo at `/usr/local/bin/cargo`, plus the locked Rust
meter dependencies cached for its offline build. Do not run Clippy or Cargo's
built-in test runner. Output includes all cfg branches and inactive test items.

The publication's metrics.json adds the previously executed validation results,
source preservation checks, and report hashes to the size measurements. Its
public test results describe only active migrated tests, not the original suite.
