# Docker build and checks

The development image uses Ubuntu 26.04 with GCC, CMake, Ninja and OpenSSL
development files. Build from the repository root:

```sh
docker build -t ops-build:ubuntu26.04 - < docker/Dockerfile.openssl_provider_sdk.ubuntu26.04
docker run --rm --mount "type=bind,source=$(pwd),target=/workspace,readonly" ops-build:ubuntu26.04
```

The default command configures a Debug build with warnings treated as errors,
builds the SDK and sample provider, and runs the registered CTest checks.
These include registry layout, an empty registry, and loading the sample provider
to fetch and exercise its digest algorithms. Only tests registered by the current
CMake configuration run; an unregistered test source is not exercised.

Recipes live in `docker/` and use `Dockerfile.{proj_name}.{desc}` names.
The recipe is self-contained: image construction uses no repository build context
and copies no files into the image. Passing the Dockerfile through standard input
enforces this boundary. Dependencies are installed by commands in the recipe.
The image contains the toolchain; it reads the real checkout at runtime.
The checkout is read-only and generated files live in `/build` inside the
disposable container. Removing the container removes these outputs. To inspect
them interactively, override the command with `sh` and omit `--rm` as needed.

For a Release build with LTO and linker garbage collection:

```sh
docker run --rm --mount "type=bind,source=$(pwd),target=/workspace,readonly" ops-build:ubuntu26.04 sh -c 'cmake -S /workspace -B /build -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON -DOPS_WARNINGS_AS_ERRORS=ON "-DCMAKE_C_FLAGS=-ffunction-sections -fdata-sections" -DCMAKE_EXE_LINKER_FLAGS=-Wl,--gc-sections -DCMAKE_MODULE_LINKER_FLAGS=-Wl,--gc-sections && cmake --build /build --parallel && ctest --test-dir /build --output-on-failure'
```

The base image is pinned by digest. Ubuntu package versions are selected when the
image is built; they are not pinned to a package snapshot. Reuse the built image
to keep the same toolchain, and rebuild deliberately for package updates.

## Build organization

The root `CMakeLists.txt` orchestrates `src/` and `test/`. Each has a local
`CMakeLists.txt`; `cmake/OpsBuildOptions.cmake`, `OpsAlgorithms.cmake`, and
`OpsInstall.cmake` cover diagnostics, registry linking, and installation.
`OpsPlatform.cmake` selects one implementation of the private platform contract
in `src/platform/`; each source directory has its own `CMakeLists.txt`.
CMake 3.24+ is required for the native `WHOLE_ARCHIVE` link feature.

`OPS_WARNINGS_AS_ERRORS=ON` enables strict diagnostics without exporting them
to installed consumers. `BUILD_TESTING=OFF` disables tests. Add `OPS_BUILD_EXAMPLES=OFF` to build only the SDK. Select tests
with `ctest --test-dir build -L registry` or `-L integration`.

Tests are grouped by scenario under `test/`: `fixtures/` contains shared
algorithm objects, `provider/` builds the loadable module using the SDK entry point, `registry/` and
`empty-registry/` check table delivery, and `fetch/` checks the OpenSSL host API.
`cli/` runs the stock `openssl list` and `openssl dgst` tools against the module,
including known-answer SHA256 checks for both directly linked and archived
algorithms. Run these with `ctest --test-dir build -L cli --output-on-failure`.
The CLI executable is required when tests are enabled. The former dummy sources
are now the working [demonstration provider](examples.md) under `example/digest/`.

`test/core/` verifies instance-specific dispatch routing, allocation and teardown
through matching core callbacks, missing optional functions, and init failure.
Public memory/BIO/core wrappers take `void *provctx` explicitly;
see [core services](core-services.md).

`test/lifecycle/` covers successful and failed user initialization, cleanup order,
per-instance state isolation, and an OpenSSL CLI run of a module with user hooks.
Select these checks with `ctest --test-dir build -L lifecycle`.

`example/` collects algorithm-class targets into `ops_example`; `test/example/`
loads the aggregate module and verifies the demonstration algorithms. Select
these checks with `ctest --test-dir build -L example`. Use `OPS_BUILD_EXAMPLES=OFF`
to omit the module and these checks.
