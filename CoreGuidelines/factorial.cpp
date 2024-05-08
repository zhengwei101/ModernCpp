//13.6
#include <iostream>

using std::cout;
using std::endl;

template<int N>
struct Factorial{
    static int const value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<1>{
    static int const value = 1;
};

int main()
{
    cout << "Factorial<10>::value: " << Factorial<10>::value << endl;
}