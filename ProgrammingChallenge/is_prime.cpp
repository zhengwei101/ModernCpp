//输入一个正整数，如何找到比它小的最大质数呢？
//如果你已经忘了什么是质数，这里简单科普一下：
//质数又称素数,是指在大于1的自然数中，除了1和它本身以外不再有其他因数的自然数。
//1不是质数。

#include <stdexcept>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::invalid_argument;

//1. 试一半就够了
//其实，稍微想一下就会发现，一个数如果可以被1和它自己之外的数整除，这个数最小就是2了。
//这也就意味着，我们只要检查[2, n/2)，如果都没发现可以整除n的数字，后面的也就不用再查了：
bool is_prime(unsigned int n) {
    for (unsigned int i = 2; i < (n / 2); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//2. 在一半里试验质数
// 在上面这个实现的for循环里，可以预见，如果n不能被2整数，那么它也注定无法被后续的所有偶数整数。
// 因此，我们只要检查[3, n/2)上所有的奇数就行了，而不用检查所有的数：
bool is_prime_ex(unsigned int n) {
    if (n % 2 == 0) {
        return false;
    }
    for (unsigned int i = 3; i < (n / 2); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


//3. 其实只查到n的平方根就行了
//我们来观察几个数字：

// 25:  1 25  /5 5
// 100: 1 100 /2 50 /4 25 /5 20 /10 10
// 发现什么了么？实际上，一个数字的所有因数，都是成对出现的。
// 在这一对数字中，一个极端情况，就是两个因数相等（例如5x5和10x10）。
// 而其他的情况，则是一个因数大于n的平方根，一个因数小于n的平方根。
// 因此，实际上我们只要从2开始，查找到n的平方根就好了，而不用查找到n/2。
bool is_prime_ex_ex(unsigned int n) {
    if (n % 2 == 0) {
        return false;
    }
    for (unsigned int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// 再优化一点点？
// 其实，在这个is_prime的实现里，我们的循环是在从3开始的奇数中进行排除的，
// 但是，如果一开始我们再把“可以被3整除”这个条件排除掉，
// 就可以让循环按照2和3的最小公倍数，也就是6作为step循环，进一步降低循环次数：
bool is_prime_ex_ex_ex(unsigned int n) {
    if (n <= 3) { return n > 1; }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

unsigned int largest_prime(unsigned int n) {
    unsigned int candidate = n - 1;

    while (candidate > 1) {
        if (is_prime_ex_ex_ex(candidate)) {
            return candidate;
        }
        --candidate;
    }
    throw invalid_argument("Invalid number");
}

int main() {
    unsigned int number;
    cout << "Input a number: ";
    cin >> number;

    try {
        unsigned int n = largest_prime(number);
        cout << "Largest primer smaller than " << number << " is " << n << endl;
    }
    catch (const invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}