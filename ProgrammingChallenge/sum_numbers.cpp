#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//让用户输入一个值，如何计算1到这个值之间所有可以被3和5整除的自然数的和呢？
int main() {
    unsigned int limit;
    cout << "input you upper limit:";
    cin >> limit;

    unsigned long long sum = 0;
    for (unsigned int i = 3; i <= limit; ++i) {
        if (i % 3 == 0 && i % 5 == 0) {
            sum += i;
        }
    }
    cout << "The sum is: " << sum << endl;
    return 0;
}