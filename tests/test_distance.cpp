#include <vsearch/distance.hpp>
#include <test_utils.hpp>

#include <vector>
#include <iostream>

#define eps 1e-5 


void test_simple(std::size_t n) {

    float a[n], b[n];
    for(std::size_t i = 0; i<n; i++) {
        a[i] = 1.0f;
        b[i] = 1.0f + i + 1;
    }

    float expected = n * (n+1) * (2*n+1) / 6;
    float actual = vsearch::l2_squared(a, b, n);

    ASSERT_FP32_EQ("test_simple, n = " + std::to_string(n), expected, actual)

}



int main() {

    test_simple(8);
    test_simple(62);
    test_simple(63);
    test_simple(64);
    test_simple(65);
    test_simple(66);

    std::cout << "All tests passed!" << std::endl;

}
