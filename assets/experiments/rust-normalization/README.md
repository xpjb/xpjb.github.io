# Current Rust normalization measurements

One comparison of the original inputs and current generated outputs; no mixed
emitters or historical appendix. Complete application sources and compiler logs
are not published. Only the displayed retry excerpt, derived data, source hashes,
and measurement tooling are included.

Reproduce sizes without editing either source tree:

    python3 measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT TAU2_INPUT TAU2_OUTPUT OUTPUT_DIR

Requires Python 3, Tokei, managed Cargo at /usr/local/bin/cargo, and cached locked
Rust meter dependencies for its offline invocation. Never use Clippy or Cargo's
built-in test runner. Total counts include all cfg branches in the listed member
src/tests/examples/benches files. Production counts exclude standalone tests/
and tests.rs files and structurally test-only items, on both sides. The generated
output omits library/binary unit suites; it preserves original integration tests.
Omitted declarations are coverage loss, not passes or proof of redundancy.

Both raw and identically formatted sizes are reported, plus lexical tokens.
Shorter physical output does not imply less production code. metrics.json adds
bounded host/default-feature validation, input integrity, preservation checks,
and exact source/report hashes. Public integration suites were also run against
scratch copies of both originals. Unit suites, Android and excluded Windows
builds are not covered by these checks.
