#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>

namespace TestPointer {
    long get_a_target_long()
    {
        long target{0};
        cout << "target (0 ~ " << RAND_MAX << "): ";
        cin >> target;
        return target;
    }

    std::string get_a_target_string()
    {
        long target{0};
        char buf[10];
        cout << "target (0 ~ " << RAND_MAX << "): ";
        cin >> target;
        snprintf(buf, 10, "%ld", target);
        return std::string(buf);
    }

    int compare_longs(const void *a, const void *b)
    {
        return(*(long*)a - *(long*)b);
    }

    int compare_strings(const void *a, const void *b)
    {
        if (*(std::string *)a > *(std::string *)b)
            return 1;
        
        if (*(std::string *)a < *(std::string *)b)
            return -1;

        return 0;
    }

    //要传递指针的引用，否则无法给pRes生成新对象
    void func_a(int* &pRes)
    {
        if(pRes == nullptr)
        {
            pRes = new int(12);
            cout << "value: " << *pRes << endl;
        }
        cout << "pointer address: " << pRes << endl;
    }

    //函数中传递指针或引用参数时，要注意修改是指针本身还是指针指向的内容
    //若不希望改变指针本身，建议加上const声明（如，func_b(int* const num))
    void func_b(int* num)
    {
        int b = 200;
        int* buf = &b;
        *num = *buf; // 要改变num指针指向的值，要解引用num
    }

    void func_c()
    {
        // 字节对齐的细节与具体编译器实现有关，不同的平台可能有所不同。
        // 一些编译器允许程序员在代码中通过预处理指令#pragma pack(n)或
        // 类型属性__attribute__((packed))来改变默认的内存对齐条件
        struct 
        {
            char flag;
            int i;
        } foo;

        foo.flag = 'T';
        
        //这里的&foo.flag+1是错误的，应该是&foo.flag+4
        //或者直接使用int* pi = &foo.i;
        int *pi = (int *)(&foo.flag + 1); //wrong
        //int *pi = (int *)(&foo.flag+4); //right
        *pi = 0x01020304;
        printf("flag=%c, i=%x\n", foo.flag, foo.i);
    }
}

void test_pointer_conversion()
{
#if 0
    long a = TestPointer::get_a_target_long() ;
    std::string b = TestPointer::get_a_target_string() ;
    cout << "target: " << a << endl;
    cout << "target: " << b << endl;

    long aa = 10;
    std::string bb{"30"};
    cout << "result: " << TestPointer::compare_longs(&a, &aa) << endl;
    cout << "result: " << TestPointer::compare_strings(&b, &bb) << endl;
#endif

    char data[4];
    *(int *)data = 114514;
    cout << "change to int*: " << *(int *)data << endl;

    *(float *)data = 1919.81;
    cout << "change to float* : "<< *(float *)data << endl;
}

void test_func()
{
    int* pInt = nullptr; 
    TestPointer::func_a(pInt);

    if(pInt)
    {
        cout << "func_a value: " << *pInt << endl;
    }

    int a = 10;
    int *num = &a;
    TestPointer::func_b(num);
    cout << "func_b num new value: " << *num << endl;

    TestPointer::func_c();
}

int main()
{
    test_func();
}