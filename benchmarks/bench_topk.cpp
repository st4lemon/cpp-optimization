#include <benchmark/benchmark.h>

#include <vsearch/topk.hpp>

#include <vector>
#include <utility>
#include <random>

static void BM_TOPK(benchmark::State& state) {
    const std::size_t dimension = state.range(0);
    const std::size_t k = state.range(1);

    std::vector<std::pair<float, std::size_t>> a(dimension);

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    
    for (std::size_t i = 0; i<dimension; i++) {
        a[i] = {dist(rng), i};
    }

    for (auto _ : state) {
        std::vector<std::pair<float, std::size_t>> result = vsearch::topk(
            a,
            dimension,
            k
        );

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_TOPK)
    ->Args({32, 8})
    ->Args({64, 8})
    ->Args({128, 8})
    ->Args({256, 8})
    ->Args({512, 8})
    ->Args({1024, 8})
    ->Args({32, 10})
    ->Args({64, 20})
    ->Args({128, 30})
    ->Args({256, 40})
    ->Args({512, 50})
    ->Args({1024, 60});

BENCHMARK_MAIN();