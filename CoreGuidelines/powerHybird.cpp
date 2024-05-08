//13.6

#include <iostream>
#include <format>

using std::cout;
using std::endl;

template<int n>
int power(int m)
{
    return m * power<n-1>(m);
}

template<>
int power<1>(int m)
{
    return m;
}

template<>
int power<0>(int )
{
    return 1;
}

int main()
{
    cout << std::format("power<10>(2): {}", power<10>(2)) << endl;
    auto power2 = power<2>;
    for(int i = 0; i<=10; ++i)
    {
        cout << std::format("power2({}) = {}", i, power2(i)) << endl;
    }

}