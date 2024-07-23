#include <stdexcept>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::invalid_argument;

// 让编译器判断是否是质数
template <int M, int N = M - 1>
struct is_prime
{
    static_assert(M > 1, "M must be greater than 1.");
    static const bool result = (M % N) && is_prime<M, N - 1>::result;
};

// 给编译器定义一个编译时的递归终止条件
template <int N>
struct is_prime<N, 1>
{
    static const bool result = true;
};

// 让编译器计算小于N的最大质数
template <int N>
struct max_prime
{
    static const int result = is_prime<N - 1>::result ? (N - 1) : max_prime<N - 1>::result;
};

// 约束一个终止条件。
// 这个终止条件，就是遍历到最小的质数
template<>
struct max_prime<3>{
    static const int result = 2;
};

// 利用模板特化，让某些语法错误的代码无法通过编译
template<>
struct max_prime<2>{
};

template<>
struct max_prime<1>{
};

int main() {
    cout << "Largest prime smaller than 23 is: " << max_prime<23>::result << endl;
    return 0;
}