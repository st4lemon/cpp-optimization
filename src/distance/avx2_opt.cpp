#include <immintrin.h>

#include <vsearch/distance.hpp>

namespace vsearch {

float l2_squared(
    const std::vector<float> &a,
    const std::vector<float> &b,
    std::size_t dimension
) {

    __m256 res0 = _mm256_setzero_ps();
    __m256 res1 = _mm256_setzero_ps();
    __m256 res2 = _mm256_setzero_ps();
    __m256 res3 = _mm256_setzero_ps();
    std::size_t i = 0;
    for(; i + 32 <= dimension; i += 32) {
        __m256 x0 = _mm256_loadu_ps(a.data() + i);
        __m256 y0 = _mm256_loadu_ps(b.data() + i);
        
        __m256 x1 = _mm256_loadu_ps(a.data() + i + 8);
        __m256 y1 = _mm256_loadu_ps(b.data() + i + 8);

        __m256 x2 = _mm256_loadu_ps(a.data() + i + 16);
        __m256 y2 = _mm256_loadu_ps(b.data() + i + 16);
        
        __m256 x3 = _mm256_loadu_ps(a.data() + i + 24);
        __m256 y3 = _mm256_loadu_ps(b.data() + i + 24);

        x0 = _mm256_sub_ps(x0, y0);
        x1 = _mm256_sub_ps(x1, y1);
        x2 = _mm256_sub_ps(x2, y2);
        x3 = _mm256_sub_ps(x3, y3);
        
        res0 = _mm256_fmadd_ps(x0, x0, res0);
        res1 = _mm256_fmadd_ps(x1, x1, res1);
        res2 = _mm256_fmadd_ps(x2, x2, res2);
        res3 = _mm256_fmadd_ps(x3, x3, res3);
    }

    res0 = _mm256_add_ps(res0, res1);
    res2 = _mm256_add_ps(res2, res3);
    res0 = _mm256_add_ps(res0, res2);


    alignas(32) float values[8];
    _mm256_store_ps(values, res0);

    float ret = 0.0f;

    for(; i<dimension; i++) {
        ret += (a[i] - b[i]) * (a[i] - b[i]);
    }

    for(i = 0; i<8; i++) {
        ret += values[i];
    }

    return ret;

}

} // vsearch
