#include <benchmark/benchmark.h>

#include <vsearch/argmin.hpp>

#include <vector>
#include <utility>

static void BM_ARGMIN(benchmark::State& state) {
    const std::size_t dimension = state.range(0);

    std::vector<float> a(dimension);

    for (auto _ : state) {
        std::pair<float, std::size_t> result = vsearch::argmin(
            a.data(),
            dimension
        );

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_ARGMIN)
    ->Arg(32)
    ->Arg(64)
    ->Arg(128)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024);

BENCHMARK_MAIN();