//13.6

#include <iostream>

using std::cout;
using std::endl;

int power(int m, int n)
{
    int r = 1;
    for(int k=1; k<=n; k++)
    {
        r *= m;
    }
    return r;
}

template<int m, int n>
struct Power{
    static int const value = m * Power<m,n-1>::value;
};

template<int m>
struct Power<m, 0>{
    static int const value = 1;
};

int main()
{
    std::cout << "power(2,10)= " << power(2,10) << endl;
    std::cout << "Power<2,10>::value= " << Power<2,10>::value << endl;

}