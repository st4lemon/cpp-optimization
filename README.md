# cpp-optimizations

A learning repository for SIMD/vectorized distance kernels with the long-term goal of implementing vector search components such as HNSW and IVF-PQ.

This project explores:
- using a CMake-based build system with different backends
- AVX2 and AVX-512 SIMD operations
- benchmark-driven performance comparison

## Project Structure

- `src/`: backend implementations for distance and vector operations
- `include/`: public headers and kernel interfaces
- `tests/`: unit tests for correctness
- `benchmarks/`: Google Benchmark harness for performance measurement

## Build and run

This project currently supports a number of backends:
- `scalar`: Standard implementation
- `avx2`: Simple AVX2 implementation
- `avx2-opt`: Optimized AVX2

### Configure

Create a Release build for the scalar backend:

    cmake -S . -B build-scalar \
        -DCMAKE_BUILD_TYPE=Release \
        -DVSEARCH_BACKEND=scalar


### Build

Build the scalar version:

    cmake --build build/scalar


## Testing

Run scalar tests:

    ctest --test-dir build/scalar --output-on-failure


## Benchmarks

Run the scalar distance benchmark:

    ./build/scalar/benchmarks/bench_distance

Show benchmark options:

    ./build/scalar/benchmarks/bench_distance --help

Run a specific benchmark pattern:

    ./build/scalar/benchmarks/bench_distance \
        --benchmark_filter=BM_L2/128

## Adding a new kernel

1. Define the kernel in a header file under `include/`.
2. Add a folder under `src/` for backend implementations.
3. Create unit tests in `tests/` and add the executable to `tests/CMakeLists.txt`.
4. Create benchmarking scripts in `benchmarks/` and add the executable to `benchmarks/CMakeLists.txt`.

## Adding a new backend

1. For each kernel, implement the new backend under `src/<kernel>/`.
2. Update `src/CMakeLists.txt` to add a new library for the backend: 
```
add_library(vsearch_backend_<backend-name> STATIC
    <kernel-1>/<backend-name>.cpp
    ...
    <kernel-n>/<backend-name>.cpp
)

target_include_directories(vsearch_backend_<backend-name>
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(vsearch_backend_<backend-name>
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        <backend-specific flags>
)
```
3. For each kernel, add an implementation using the new backend as `src/<kernel>/<backend-name>.cpp`
4. Configure a new build directory for the backend, for example:
```a
cmake -S . -B build/<backend-name> \
    -DCMAKE_BUILD_TYPE=Release \
    -DVSEARCH_BACKEND=<backend-name>
```
5. Build and run tests/benchmarks for the new backend.

## Notes

- This repository is primarily educational: the focus is on understanding and comparing kernel implementations.
- Performance results depend on CPU features and compiler flags.


### Machine Specs
|Item|Description|
|-|-|
|CPU|AMD Ryzen 7 7800X3D| 
|Cores/Threads|8/16|
|Base/Boost Clock|4.2/5.0 GHz| 
|L1/L2/L3 cache|512KB/8MB/96MB|
|SIMD ISAs|AVX, AVX2, AVX-512, FMA3|
|YMM width|256-bit|
|Memory|2x16GB G.Skill DDR5-6000|
|Memory Channels|2|
|GPU|RTX 3060 12GB|
