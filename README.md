# cpp-optimizations

# Building

The project uses CMake.

## Configure

Create a Release build for the scalar backend:

    cmake -S . -B build-scalar \
        -DCMAKE_BUILD_TYPE=Release \
        -DVSEARCH_BACKEND=scalar

Create a Release build for the AVX2 backend:

    cmake -S . -B build-avx2 \
        -DCMAKE_BUILD_TYPE=Release \
        -DVSEARCH_BACKEND=avx2

## Build

Build the scalar version:

    cmake --build build-scalar

Build the AVX2 version:

    cmake --build build-avx2

## Tests

Run the scalar tests:

    ctest --test-dir build-scalar --output-on-failure

Run the AVX2 tests:

    ctest --test-dir build-avx2 --output-on-failure

## Benchmarks

Run the scalar distance benchmark:

    ./build-scalar/benchmarks/bench_distance

Run the AVX2 distance benchmark:

    ./build-avx2/benchmarks/bench_distance

To see Google Benchmark's available options:

    ./build-avx2/benchmarks/bench_distance --help

For example, to run a specific benchmark:

    ./build-avx2/benchmarks/bench_distance \
        --benchmark_filter=BM_L2/128