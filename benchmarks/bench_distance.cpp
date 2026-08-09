#include <benchmark/benchmark.h>

#include <vsearch/distance.hpp>

#include <vector>

static void BM_L2(benchmark::State& state) {
    const std::size_t dimension = state.range(0);

    std::vector<float> a(dimension);
    std::vector<float> b(dimension);

    for (auto _ : state) {
        float result = vsearch::l2_squared(
            a.data(),
            b.data(),
            dimension
        );

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_L2)
    ->Arg(32)
    ->Arg(64)
    ->Arg(128)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024);

BENCHMARK_MAIN();