#include <iostream>
using std::cout;
using std::endl;

#include "string.h"

int main()
{
    MString s1("hello");
    MString s2("world");

    MString s3(s2); // s3不存在，所以调用的是拷贝构造
    // MString s3 = s2; //注意，这里调用的也是拷贝构造，和上面一样，此时s3也是不存在的。
    cout << s3 << endl;

    s3 = s1; // s3已存在，所以调用的是拷贝赋值(copy assignment operator)

    cout << s3 << endl;
    cout << s2 << endl;
    cout << s1 << endl;
}
