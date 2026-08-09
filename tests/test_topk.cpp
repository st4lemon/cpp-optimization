#include <vsearch/topk.hpp>
#include <test_utils.hpp>

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

#define eps 1e-5 
#define mod 998244353

void test_topk(std::size_t n, std::size_t k) {

    std::vector<std::pair<float, std::size_t>> a(n);
    int32_t val = 93415;
    for(std::size_t i = 0; i<n; i++) {
        a[i] = {val, i};
        val = 2*val % mod;
    }

    std::mt19937 rd(std::random_device{}());
    std::vector<std::pair<float, std::size_t>> actual = vsearch::topk(a, n, k, rd);
    std::sort(actual.begin(), actual.end());

    std::sort(a.begin(), a.end());

    std::vector<std::pair<float, std::size_t>> expected{a.begin(), a.begin()+k};

    for(std::size_t i = 0; i<k; i++) {
        ASSERT_FP32_EQ("test_topk val, n = " + std::to_string(n) + " i = " + std::to_string(i), expected[i].first, actual[i].first);
        ASSERT_INT32_EQ("test_topk ind, n = " + std::to_string(n) + " i = " + std::to_string(i), expected[i].second, actual[i].second);
    }
}



int main() {

    test_topk(8, 1);
    test_topk(62, 10);
    test_topk(63, 10);
    test_topk(64, 10);
    test_topk(65, 10);
    test_topk(66, 10);
    test_topk(16384, 30);

    std::cout << "All tests passed!" << std::endl;

}
