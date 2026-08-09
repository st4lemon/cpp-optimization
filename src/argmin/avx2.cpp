#include <vsearch/argmin.hpp>
#include <immintrin.h>
#include <limits>
#include <iostream>

namespace vsearch {

std::pair<float, std::size_t> argmin(
    const float* a,
    std::size_t n
) {

    __m256 res = _mm256_set1_ps(std::numeric_limits<float>::max());
    __m256i best_idx = _mm256_setzero_si256();

    __m256i idx = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
    const __m256i eight = _mm256_set1_epi32(8);

    std::size_t i = 0;

    
    for(; i + 8 <= n; i += 8) {
        __m256 x = _mm256_loadu_ps(a+i);
        
        // get all locations that are better
        __m256 msk = _mm256_cmp_ps(x, res, _CMP_LT_OQ);

        // update res
        res = _mm256_blendv_ps(res, x, msk);

        // update best indexes
        best_idx = _mm256_castps_si256(
            _mm256_blendv_ps(
                _mm256_castsi256_ps(best_idx), 
                _mm256_castsi256_ps(idx), 
                msk
            )
        );
        
        idx = _mm256_add_epi32(idx, eight);

    }

    // reduce res and best_idx.
    
    __m256 v = res;

    v = _mm256_min_ps(v, _mm256_permute2f128_ps(v, v, 1));
    v = _mm256_min_ps(v, _mm256_shuffle_ps(v, v, _MM_SHUFFLE(1, 0, 3, 2)));
    v = _mm256_min_ps(v, _mm256_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1)));

    float min_val = _mm_cvtss_f32(_mm256_castps256_ps128(v));

    
    __m256 msk = _mm256_cmp_ps(res, v, _CMP_EQ_OQ); // sets all bits 1 if cmp succees, else all bits 0
    int lanes = _mm256_movemask_ps(msk); // get sign bit of each lane
    
    // broadcast value to all elements of best_idx
    best_idx = _mm256_permutevar8x32_epi32(
        best_idx,
        _mm256_set1_epi32(__builtin_ctz(lanes))
    );

    int min_idx = _mm_cvtsi128_si32(_mm256_castsi256_si128(best_idx));
    for(; i < n; ++i) {
        if(a[i] < min_val) {
            min_val = a[i];
            min_idx = i;
        }
    }

    return {min_val, min_idx};

}

} // vsearch