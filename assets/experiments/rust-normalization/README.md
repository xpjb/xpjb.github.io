# Current Rust normalization measurements

All metrics and trees compare the original inputs with the retained generated
snapshots. Current hardened regeneration is blocked at test migration, so these
measurements and older active-suite receipts are not a current correctness claim. There is no mixed-emitter or historical appendix. Complete application
sources and private compiler logs are not published; only the displayed retry
excerpt, derived data, source hashes, and measurement tooling are included.

Reproduce sizes without editing either source tree:

    python3 measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT TAU2_INPUT TAU2_OUTPUT OUTPUT_DIR

Requires Python 3, Tokei, managed Cargo at /usr/local/bin/cargo, and the locked
Rust meter dependencies cached for the offline invocation. Never use Clippy or
Cargo's built-in test runner. The script counts all cfg branches and inactive
test items within member-package src/tests/examples/benches directories.

metrics.json adds separately executed validation, original source integrity,
preservation checks and report hashes. Its test counts describe active migrated
public-interface tests, not the original suite. Windows source and build scripts
are preserved; excluded Windows manifests can have formatting-only differences.
Neither Android nor excluded Windows targets were built for this validation.
