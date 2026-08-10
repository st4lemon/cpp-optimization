#include <immintrin.h>

namespace common {

const __m256i swap[6] = {
    _mm256_setr_epi32(1, 0, 3, 2, 5, 4, 7, 6),
    _mm256_setr_epi32(2, 3, 0, 1, 6, 7, 4, 5),
    _mm256_setr_epi32(1, 0, 3, 2, 5, 4, 7, 6),
    _mm256_setr_epi32(4, 5, 6, 7, 0, 1, 2, 3),
    _mm256_setr_epi32(2, 3, 0, 1, 6, 7, 4, 5),
    _mm256_setr_epi32(1, 0, 3, 2, 5, 4, 7, 6)
};

const __m256 asc[6] = {
    _mm256_setr_ps(0, -1, -1, 0, 0, -1, -1, 0), // 0 picks min, -1 picks max
    _mm256_setr_ps(0, 0, -1, -1, -1, -1, 0, 0),
    _mm256_setr_ps(0, -1, 0, -1, -1, 0, -1, 0),
    _mm256_setr_ps(0, 0, 0, 0, -1, -1, -1, -1),
    _mm256_setr_ps(0, 0, -1, -1, 0, 0, -1, -1),
    _mm256_setr_ps(0, -1, 0, -1, 0, -1, 0, -1)
};

inline void sort8(
    __m256 &v,
    __m256i &inds
) {

    __m256 pv;
    __m256i pinds;
    __m256 msk;

    // stage 1
    // permute the values and inds
    for(int i = 0; i<6; i++) {
        pv = _mm256_permutevar8x32_ps(v, swap[i]);
        pinds = _mm256_permutevar8x32_epi32(inds, swap[i]);

        // get positions of v that are lower
        // 1 0 0 1 0 1 1 0
        msk = _mm256_cmp_ps(v, pv, _CMP_LT_OQ); 

        msk = _mm256_xor_ps(msk, asc[i]);

        inds = _mm256_castps_si256(
            _mm256_blendv_ps(
                _mm256_castsi256_ps(pinds), 
                _mm256_castsi256_ps(inds),
                msk
            )
        );

        v = _mm256_blendv_ps(
            pv,
            v,
            msk
        );

    }


}

}