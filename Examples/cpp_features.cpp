#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string.h>

#include <exception>
#include <stdexcept>
#include <typeinfo>

#include <assert.h>
#include <vector>
#include <bitset>
#include <tuple>
#include <string>
#include <memory>
#include <algorithm>

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

    void testPrintf()
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

    void testLambda()
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

        std::vector<int> someList{1, 2, 3, 4, 5, 9, 8, 7, 6};
        int total = 0;
        std::for_each(begin(someList), end(someList), [&total](int x)
                      { total += x; });
        std::cout << total << std::endl; // 输出45
    }

}

namespace Test_Size
{
#pragma GCC diagnostic ignored "-Wsizeof-array-argument"
    struct MyStruct
    {
        int a;
        double b;
        char c;
    };

    void func(char str[])
    {
        // 数组作为函数参数时会退化为指针，大小要按指针的计算
        cout << "size of str param: " << sizeof(str) << endl; // 8
    }

    /*
    size_t strlen(const char* str)
    {
        size_t length = 0;
        while(*str++) {
            ++length;
        }
        return length;
    }
    */
    void testSize()
    {
        char str[] = "Hello,world!";
        cout << "size of str: " << sizeof(str) << endl; // 13, 12个字符 + 末尾'\0'

        // strlen 是一个 C 标准库中的函数，用于计算 C 风格字符串（以空字符 '\0' 结尾的字符数组）的长度，
        // 即不包括结尾的空字符的字符个数。
        cout << "Lenght of str: " << strlen(str) << endl; // 12

        func(str);

        cout << "size of MyStruct: " << sizeof(MyStruct) << endl; // 24

        int arr[10];
        cout << "size of arr: " << sizeof(arr) << endl; // 40

        struct EmptyStruct
        {
        };
        cout << "size of EmptyStruct: " << sizeof(EmptyStruct) << endl; // 1
    }
#pragma GCC diagnostic error "-Wsizeof-array-argument"
}

namespace Test_SMartPtr
{
    class X : public std::enable_shared_from_this<X>
    {
    public:
        std::shared_ptr<X> getPtr()
        {
            return shared_from_this();
        }
        X *getRawPtr()
        {
            return this;
        }
    };

    void testSharedFromThis()
    {
        std::shared_ptr<X> p(new X);
        std::shared_ptr<X> q = p->getPtr();

        X *r = p->getRawPtr();
        assert(p == q);
        assert(p.get() == r);

        cout << p.use_count() << endl;
        std::shared_ptr<X> s(r);
        cout << s.use_count() << endl;
        // assert(p == s);
    }
}

namespace Test_Ptr
{
    int (*ptr1)(); //函数指针

    int text() {   //返回int的函数
        return 65;
    }

    int a = 20;
    int* ptr2() {  //返回int*的函数
        return &a;
    }

    void testFuncPtr()
    {
        ptr1 = text;
        cout << "call ptr1: " << ptr1() << endl;
        cout << "call ptr2: " << *ptr2() << endl;
    }
}

int main()
{
    // Test_Variadic_Template::testPrintf();
    // Test_Lambda::testLambda();
    // Test_Size::testSize();

    Test_Ptr::testFuncPtr();

    return 0;
}