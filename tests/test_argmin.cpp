#include <vsearch/argmin.hpp>
#include <test_utils.hpp>

#include <vector>
#include <iostream>

#define eps 1e-5 
#define mod 998244353

void test_argmin(std::size_t n) {

    float a[n];
    int32_t val = 9;
    std::pair<float, std::size_t> expected{mod+1, 0};
    for(std::size_t i = 0; i<n; i++) {
        a[i] = val;
        if(expected.first > a[i]) expected = {a[i], i};
        val = 2*val % mod;
    }

    std::pair<float, std::size_t> actual = vsearch::argmin(a, n);

    ASSERT_FP32_EQ("test_argmin, n = " + std::to_string(n), expected.first, actual.first);
    ASSERT_INT32_EQ("test_argmin, n = " + std::to_string(n), expected.second, actual.second);

}



int main() {

    test_argmin(8);
    test_argmin(62);
    test_argmin(63);
    test_argmin(64);
    test_argmin(65);
    test_argmin(66);

    std::cout << "All tests passed!" << std::endl;

}
