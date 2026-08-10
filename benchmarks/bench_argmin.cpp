#include <benchmark/benchmark.h>

#include <vsearch/argmin.hpp>

#include <vector>
#include <utility>
#include <random>

static void BM_ARGMIN(benchmark::State& state) {
    const std::size_t dimension = state.range(0);

    std::vector<float> a(dimension);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (float& x : a)
        x = dist(rng);

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