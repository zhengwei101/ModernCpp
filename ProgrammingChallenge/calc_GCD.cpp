//用递归和非递归的方法计算用户输入的两个自然数的最大公约数（Greatest Common Divisor）。

//计算GCD，最行之有效的方法就是欧几里得公式：
// gcd(m, 0) = m
// gcd(m, n) = gcd(n, m % n)

// 为此，我们可以把这个公式直接变成递归算法：
unsigned int gcd_recursive(unsigned int const m, unsigned int const n) {
    return n == 0 ? m : gcd_recursive(n, m % n);
}

//而这个算法的非递归形式，就是把计算过程写在一个循环里：
unsigned int gcd_nonrecursive(unsigned int m, unsigned int n) {
    while (n != 0) {
        unsigned int mod = m % n;
        m = n;
        n = mod;
    }
    return m;
}

//实际上，在C++17之后，<numeric>头文件中还引入了一个gcd方法，我们直接拿来用就行了：

#include <numeric>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    cout << "Input two numers separated by space: ";
    unsigned int m = 0;
    unsigned int n = 0;

    cin >> m >> n;

    cout << "GCD recurisve: " << gcd_recursive(m, n) << endl;
    cout << "GCD recurisve: " << gcd_nonrecursive(m, n) << endl;
    cout << "GCD recurisve: " << std::gcd(m, n) << endl;

    return 0;
}
