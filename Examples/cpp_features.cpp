#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <exception>
#include <stdexcept>
#include <typeinfo>

#include <bitset>
#include <tuple>
#include <string>

namespace Test_Variadic_Template
{

    void printX() {}

    template <typename T, typename... Types>
    void printX(const T &firstArg, const Types &...args)
    {
        cout << firstArg << endl;
        printX(args...);
    }

    // 下面这个函数可以和上面的printX函数共存
    // 思考： 谁较泛化？谁较特化？
    template <typename... Types>
    void printX(const Types &...args)
    {
        cout << "no firstArg" << endl;
        printX(args...);
    }

    // print element with index IDX of tuple with MAX elements
    template <int IDX, int MAX, typename... Args>
    struct PRINT_TUPLE
    {
        static void print(std::ostream &os, const std::tuple<Args...> &t)
        {
            os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
            PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);
        }
    };

    // partial specialization to end the recursion
    template <int MAX, typename... Args>
    struct PRINT_TUPLE<MAX, MAX, Args...>
    {
        static void print(std::ostream &, const std::tuple<Args...> &)
        {
            // do nothing
        }
    };

    template <typename... Args>
    std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &t)
    {
        os << "[";
        PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
        os << "]";
        return os;
    }

    void myPrintf(const char *s)
    {
        while (*s)
        {
            if (*s == '%' && *(++s) != '%')
            {
                throw std::runtime_error("invalid format string: missing arguments");
            }
            std::cout << *s++;
            std::cout << "##" << endl; // 正常退出
        }
    }

    template <typename T, typename... Args>
    void myPrintf(const char *s, T value, const Args &...args)
    {
        while (*s)
        {
            if (*s == '%' && *(++s) != '%')
            {
                cout << value;
                myPrintf(++s, args...);
                return;
            }
            std::cout << *s++;
        }
        throw std::logic_error("extra arguments provided to printf");
    }

    void test_Printf()
    {
        printX(7.5, "hello", std::bitset<16>(377), 42);
        cout << "----------------------------------------" << endl;
        cout << std::make_tuple(7.5, std::string("hello"), std::bitset<16>(377), 42) << endl;
        cout << "----------------------------------------" << endl;

        int *pi = new int;
        myPrintf("%d %s %p %f\n", 123, "abc", pi, 3.1415926);
        cout << "----------------------------------------" << endl;

        try
        {
            myPrintf("%d %s %p %f\n", 123, "abc", pi, 3.1415926, "extra");
        }
        catch (const std::exception &e)
        {
            cerr << "Caught: " << e.what() << endl;
            cerr << "Type: " << typeid(e).name() << endl;
        }
    }
}

namespace Test_Lambda
{
    class Functor
    {
    private:
        int id = 1; // copy of outside id
    public:
        void operator()()
        {
            std::cout << "Functor::id: " << id << std::endl;
            ++id;
        }
    };

    void test_Functor()
    {
        int id = 0;
        // auto f = [id]() mutable  //注意，这里不加mutable，就不能++id
        auto f = [&id](int param) // 注意, 这里用引用的方式, 会改为id的值
        {
            ++id;
            ++param;
            cout << "id: " << id << endl;
            cout << "param: " << param << endl;
        };

        Functor ff;
        ff();

        id = 100;
        f(7);
        f(7);
        f(7);
        cout << "after call f(), id: " << id << endl;
    }
}

int main()
{
    Test_Variadic_Template::test_Printf();

    // Test_Lambda::test_Functor();

    return 0;
}