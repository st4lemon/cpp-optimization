#include <common/sort.hpp>
#include <test_utils.hpp>

#include <vector>
#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

#include <immintrin.h>

void test_sort8() {

    static thread_local std::mt19937 rng(12345);
    static thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<std::pair<float, std::size_t>> a(8);
    for(int i = 0; i<8; i++)
        a[i] = {dist(rng), i};

    __m256 v = _mm256_setr_ps(
        a[0].first,
        a[1].first,
        a[2].first,
        a[3].first,
        a[4].first,
        a[5].first,
        a[6].first,
        a[7].first
    );

    __m256i ind = _mm256_setr_epi32(
        a[0].second,
        a[1].second,
        a[2].second,
        a[3].second,
        a[4].second,
        a[5].second,
        a[6].second,
        a[7].second
    );

    common::sort8(v, ind);

    std::sort(a.begin(), a.end());

    alignas(32) float res[8];
    alignas(32) uint32_t inds[8];
    _mm256_store_ps(res, v);
    _mm256_store_si256(reinterpret_cast<__m256i*>(inds), ind);
    for(std::size_t i = 0; i<8; i++) { 
        std::cout << res[i] << " " << inds[i] << " | ";
    }
    std::cout << std::endl;
    for(std::size_t i = 0; i<8; i++) { 
        std::cout << a[i].first << " " << a[i].second << " | ";
    }
    std::cout << std::endl;

    for(std::size_t i = 0; i<8; i++) {
        ASSERT_FP32_EQ("test_sort8 i = " + std::to_string(i), a[i].first, res[i]);
        ASSERT_INT32_EQ("test_sort8 i = " + std::to_string(i), a[i].second, inds[i]);
    }

}



int main() {

    for(int i = 0; i<10000; i++) {
        test_sort8();
        std::cout << "Test " << i << " passed..." << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;


}
