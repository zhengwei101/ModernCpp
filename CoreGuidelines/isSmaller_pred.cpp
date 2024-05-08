//13.3
#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;

class Account {
public:
    Account() = default;
    Account(double b):balance(b){}
    double getBalance() const 
    {
        return balance;
    }
private:
    double balance{0.0};
};

//使用扩展
template<typename T, typename Pred = std::less<T>>
bool isSmaller(T fir, T sec, Pred pred = Pred())
{
    return pred(fir,sec);
}

int main()
{
    cout << std::boolalpha << endl;
    double firDoub{};
    double secDoub{2014.0};
    cout << "isSmaller(firDoub, secDoub): " << isSmaller(firDoub, secDoub) << endl;

    Account firAcc{};
    Account secAcc{2014.0};
    auto res = isSmaller(firAcc, secAcc, [](const Account& fir, const Account& sec){
            return fir.getBalance() < sec.getBalance();
        });
    cout << "isSmaller(firAcc, secAcc): " << res << endl;

    std::string firStr = "AAA";
    std::string secStr = "BB";
    cout << "isSmaller(firStr, secStr): " << isSmaller(firStr,secStr) << endl;

    auto res2 = isSmaller(firStr, secStr, [](const std::string& firStr, const std::string& secStr){
        return firStr.length() < secStr.length();
    });
    cout << "isSmaller(firStr, secStr): " << res2 << endl;

}