//13.5

#include <iostream>
#include <utility>
#include <string>
#include <format>
#include <tuple>
#include <functional>

using std::cout;
using std::endl;

class MyType
{
public:
    MyType(int x, double y, bool z)
        : data(std::make_tuple(x, y, z)){};
    friend std::ostream &operator<<(std::ostream &os, const MyType &type);

private:
    std::tuple<int, double, bool> data{};
};

std::ostream &operator<<(std::ostream &os, const MyType &t)
{
    os << std::get<0>(t.data) << "," << std::get<1>(t.data) << "," << std::get<2>(t.data);
    return os;
}

template <typename T, typename... Args>
T createT(Args... args)
{
    return T(std::forward<Args>(args)...);
}

int main()
{
    int uniqZero = createT<int>();
    auto uniqEleven = createT<int>(2011);

    int lvalue(2020);
    auto uniqTwenty = createT<int>(lvalue);

    std::string output = std::format("{},{},{}", uniqZero, uniqEleven, uniqTwenty);
    cout << output << endl;

    auto uniqType = createT<MyType>(lvalue, 3.14, true);

    cout << uniqType << endl;

}