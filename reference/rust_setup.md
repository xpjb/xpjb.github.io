# Rust Setup Guide

## Prerequisites
- Git bash
- Rustup
- Visual C++ dependencies
- SSH keys

## Installation
To set up the nightly toolchain with `rustc-codegen-cranelift-preview`, run the following commands:
```bash
rustup default nightly
rustup component add rustc-codegen-cranelift-preview --toolchain nightly
```