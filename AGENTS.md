# Repository Guidelines

## Project Structure & Module Organization

This repository contains a C11 SDK for OpenSSL providers. Public headers live in `include/openssl_provider_sdk/`; implementations use the `ops_` prefix under `src/`. Platform code lives in `src/platform/`, selected by CMake behind a documented private interface. `example/` builds one demonstration provider; `test/` groups checks by scenario. Keep generated files in ignored `build/` or `out/` directories.

Keep local `CMakeLists.txt` files beside compiled sources and logical modules under `cmake/`. Prefer target usage requirements and interface libraries to functions that mutate arbitrary targets. Local skills and agent drafts under ignored `result/` are not distributed with the repository.

## Build, Test, and Development Commands

Requirements: CMake 3.24+, a C11 compiler, OpenSSL 3.0+ development files, and the `openssl` CLI for tests.

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DOPS_WARNINGS_AS_ERRORS=ON` configures a strict out-of-tree build.
- `cmake --build build --parallel` builds the SDK, examples, and enabled test targets.
- `ctest --test-dir build --output-on-failure` runs registered checks.
- `cmake --install build --prefix ./out --config Debug` stages the SDK and CMake package.

Disable tests/examples with `BUILD_TESTING=OFF` and `OPS_BUILD_EXAMPLES=OFF`. Docker and Release/LTO commands are in `docs/docker-build.md`. Windows/MSVC code exists but remains unverified by a native build.

## Coding Style & Naming Conventions

Use four spaces, Allman braces, snake_case, and uppercase header guards. Function parameters stay on one line or each get their own line. Separate completed blocks with blank lines; indent Doxygen tag continuations four additional spaces. Mark public functions `OPS_API`. Keep OS-specific implementations behind platform contracts and preserve OpenSSL entry-point names. No formatter is configured.

## Testing Guidelines

CTest covers core dispatch, parameters, linker records, lifecycle, and real OpenSSL loading. CLI checks require both exit success and expected output. Run relevant tests and exercise LTO/section GC for linker changes. Verify installed consumers when package exports change. No coverage threshold is configured; report untested platforms explicitly.

## Commit & Pull Request Guidelines

Git history contains only `Initial commit`, so no established message convention exists. Use short, imperative subjects describing one focused change. Pull requests should explain the behavior changed, relevant issues, and validation performed. State build blockers explicitly and update documentation when public APIs or build instructions change.
