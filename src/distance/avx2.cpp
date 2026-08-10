#include <immintrin.h>

#include <vsearch/distance.hpp>

namespace vsearch {

float l2_squared(
    const std::vector<float> &a,
    const std::vector<float> &b,
    std::size_t dimension
) {

    __m256 res = _mm256_setzero_ps();
    std::size_t i = 0;
    for(; i + 8 <= dimension; i += 8) {
        __m256 x = _mm256_loadu_ps(a.data() + i);
        __m256 y = _mm256_loadu_ps(b.data() + i);
        x = _mm256_sub_ps(x, y);
        res = _mm256_fmadd_ps(x, x, res);
    }

    alignas(32) float values[8];
    _mm256_store_ps(values, res);

    float ret = 0.0f;

    for(; i<dimension; ++i) {
        ret += (a[i] - b[i]) * (a[i] - b[i]);
    }

    for(i = 0; i<8; ++i) {
        ret += values[i];
    }

    return ret;

}

} // vsearch