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

    cmake -S . -B build/scalar \
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

1. Define the kernel interface in a header under `include/`.
2. Add a backend-specific implementation file in `src/<kernel>/<backend>.cpp`.
3. If this kernel is new for an existing backend, update `src/CMakeLists.txt` by adding the file to the appropriate `VSEARCH_BACKEND_SOURCES_<backend>` list.
4. Create or extend unit tests in `tests/` and keep `tests/CMakeLists.txt` backend-agnostic.
5. Add benchmark cases in `benchmarks/bench_distance.cpp`; `benchmarks/CMakeLists.txt` remains unchanged.

## Adding a new backend

1. Implement the new backend for each kernel with files such as `src/<kernel>/<backend>.cpp`.
2. In `src/CMakeLists.txt`, add the backend name to `VSEARCH_BACKENDS`.
3. Define `VSEARCH_BACKEND_SOURCES_<backend>` listing all backend source files.
4. Optionally define `VSEARCH_BACKEND_COMPILE_OPTIONS_<backend>` if the backend needs special compiler flags.
5. Update the root `CMakeLists.txt` backend option list if you want the backend to appear in the cache string suggestions.
6. Configure and build the new backend:

    cmake -S . -B build/<backend-name> \
        -DCMAKE_BUILD_TYPE=Release \
        -DVSEARCH_BACKEND=<backend-name>

7. Run tests and benchmarks for the new backend.

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

# Roadmap

```
                     0. Build system
                              │
                              ▼
                  1. SIMD distance kernels
                              │
                              ▼
                       2. Top-k kernels
                              │
                              ▼
                       3. Flat search
                              │
                              ▼
                     4. Memory layouts
                              │
                              ▼
                      5. Product Quantization
                              │
                              ▼
                    6. SIMD PQ / ADC
                              │
                              ▼
                         7. IVF-PQ
                              │
                    ┌─────────┴─────────┐
                    ▼                   ▼
             8. RP trees            9. HNSW
                    │                   │
                    └─────────┬─────────┘
                              ▼
                   10. Runtime dispatch
                              │
                              ▼
                  11. Compiler vs intrinsics
                              │
                              ▼
                  12. Deep performance profiling
```
