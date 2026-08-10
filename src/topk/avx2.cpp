
#include <vector>
#include <utility>
#include <random>
#include <algorithm>

namespace vsearch {

    
void quickselect(std::vector<std::pair<float, std::size_t>> &a, std::size_t l, std::size_t r, std::size_t k, std::mt19937 &rng) {
    // choose random pivot
    while(l < r) {
        std::pair<float, std::size_t> p = a[rng() % (r-l+1) + l];
        
        std::size_t lo = l, i = l, hi = r;
        // [l, lo) : < p
        // [lo, i) : == p 
        // (hi, r] : > p
        while(i <= hi) {
            if (a[i] < p) std::swap(a[lo++], a[i++]);
            else if (a[i] > p) std::swap(a[i], a[hi--]);
            else ++i;
        }

        if(k < lo) r = lo-1;
        else if(k <= hi) return;
        else l = hi+1;

    }

}

std::vector<std::pair<float, std::size_t>> topk(
    std::vector<std::pair<float, std::size_t>> &a,
    std::size_t n, 
    std::size_t k
) {

    static thread_local std::mt19937 rng;

    // run quickselect on b
    if(k < n) quickselect(a, 0, n-1, k, rng);

    // sort(a.begin(), a.end());

    return {a.begin(), a.begin()+std::min(k, n)};
}

} // vsearch