//13.3
#include <iostream>
using std::cout;
using std::endl;

class Account {
public:
    Account() = default;
    Account(double b):balance(b){}
    //方式一，重载 operator < 
    // friend bool operator <(const Account& fir,const Account& sec)
    // {
    //     return fir.getBalance() < sec.getBalance();
    // }
    double getBalance() const 
    {
        return balance;
    }
private:
    double balance{0.0};
};

template<typename T>
bool isSmaller(T fir, T sec)
{
    return fir < sec;
}

//方式二，比较函数的全特化
// template<>
// bool isSmaller(Account fir, Account sec)
// {
//     return fir.getBalance() < sec.getBalance();
// }

//方式三， 函数重载
bool isSmaller(Account fir, Account sec)
{
    return fir.getBalance() < sec.getBalance();
}

int main()
{
    cout << std::boolalpha << endl;
    double firDoub{};
    double secDoub{2014.0};
    cout << "isSmaller(firDoub, secDoub): " << isSmaller(firDoub, secDoub) << endl;

    Account firAcc{};
    Account secAcc{2014.0};
    cout << "isSmaller(firAcc, secAcc): " << isSmaller(firAcc, secAcc) << endl;
}