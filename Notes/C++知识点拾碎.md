# C/C++ 知识点

## 将文件全部内容读入string

```c++
std::ifstream file("test.txt");

std::string contex((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
```

注意这里第一个参数外面的括号不能少。

这里的原理是利用`std::string`的一个构造函数：以迭代器作为参数的那个构造函数。

这里构造了`std::istreambuf`的迭代器，所以可以直接使用构造函数传入。

## `enum class`

原本兼容C的`enum`有如下特点：

- 枚举项是公开的，在全局下是全局的，在类中是属于类的
- 可以隐式转换为整型
  

第一点导致在同一作用域下不同的枚举类型不能够声明相同的枚举项：

```C++
enum A{
    E_A,
    E_B
};

enum B{
    E_B, //ERROR! redefinition of enumerator 'E_B'
    E_C
};
```

第二点可能会导致隐藏Bug。

所以`C++11`推出了`enum class`，有如下特点：

- 具有封装性，即枚举量不再是全局的，访问也必须加上枚举类型的名字
- 不能和整型互相隐式转换
- 可以指定枚举类型中枚举值的变量类型

```c++
enum class A{
    E_A,
    E_B
};

//可指定枚举值的数据类型
enum class B:unsigned int{  
    E_B = 0,
    E_C   
};

//访问时要带上枚举类的名字
A::E_A;
int x = static_cast<int>(A::E_B); //需要强制转换
```

## C++ new赋予初值的问题

`C++`中如果你是对基本数据类型进行`new`的话是不会初始化的。

但是如果你在最后加上()会初始化为0。

```c++
int* p = new int;   //no initialize
int* p = new int(); //initialize
```

如果是类的话，如果类有默认构造函数，那么会调用默认构造函数（无论有没有加括号）。

如果没有，你需要显式传入参数来调用构造函数。

```c++
#include <iostream>
using std::cout;
using std::endl;

class Person
{
public:
    int age;
    int height;
    Person(int age, int height)
    {
        this->age = age;
        this->height = height;
    }
};

int main()
{
    Person *p = new Person(10, 120);
    cout << p->age << endl
         << p->height << endl;
}
```

如果是数组的话，基本数据类型仍然要加上()才能初始化。

但是类的话必须要有默认构造函数，因为这个时候`C++`不允许你传入参数。

```c++
#include <iostream>
using std::cout;
using std::endl;

class Person
{
public:
    int age;
    int height;
    Person()
    {
        age = 10;
        height = 120;
    }
};

int main()
{
    int* arr = new int[2](); //对数组进行初始化

    Person* p = new Person[10];
    cout<<p[2].age<<endl<<p[2].height<<endl;
}
```

## 关于内存释放的问题

假如有以下代码

```c++
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *array;
} sa;

typedef struct{
    sa *a;
} sb;

typedef struct{
    sb *b;
} sc;

int main() {
    sc *c = NULL;
    while (1) //这里死循环，查看是否有内存泄露
    {
        // malloc memory
        c = (sc*)malloc(sizeof(sc));
        c->b = (sb*)malloc(sizeof(sb));
        c->b->a = (sa*)malloc(sizeof(sa));
        c->b->a->array = (int*)malloc(sizeof(int) * 10);

        // free memory
        free(c);
        c = NULL;
        cout <<"does all pointers free ?" << endl;
    }
}
```

这里的`free(c)`可以将c变量中的b变量，b变量中的a变量，a变量中的array一同释放掉吗？

答案是不行的。

对于使用多次`malloc()`的内存，要相应地使用`free()`依次释放才可以：

```c++
    // free memory
    free(c->b->a->array);
    c->b->a->array = NULL;
    free(c->b->a);
    c->b->a = NULL;
    free(c->b);
    c->b = NULL;
    free(c);
    c = NULL;
    cout <<"yes, all pointers free." << endl;
```

对于`C++`的`new`和`delete`是一个道理。

此外，在Unix系统上判断内存泄漏的方法：

将你认为会内存泄漏的代码放在死循环里面循环，

然后用`top -pid`命令打印出这个程序的信息，查看`MEM`字段，

如果其字段恒定不变的话，就没有泄漏，如果一直在增长就是泄漏了。

## 数组做参数退化为指针
数组退化：在 C++ 中，数组在作为函数参数时会退化为指向其首元素的指针。

退化的原因是因为数组作为函数参数时，实际传递的是指向数组首元素的指针，不可能逐个拷贝整个数组然后在栈上传递，所以编译器只知道参数是一个指针，而不知道它的长度信息。

但是，当数组直接作为 `sizeof`的参数时，它不会退化，因为`sizeof`是编译器在编译期间计算的结果，这个时候编译器是有信息知道数组的大小。

为了在函数中获取数组的长度，需要将数组的长度作为另一个参数传递给函数，或者使用模板实现。

## 数组的引用做参数

```c++
#include <iostream>
#include <cstring>
template <typename T, std::size_t N>
void printSizeAndLength(const T (&arr)[N]) {
    std::cout << "Size of arr in function: " << sizeof(arr) << std::endl; // 计算数组的大小
    std::cout << "Length of arr: " << strlen(arr) << std::endl; // 计算字符串的长度
}
int main() {
    char str[] = "Hello, world!";
    std::cout << "Size of str in main: " << sizeof(str) << std::endl; // 计算整个字符数组的大小
    printSizeAndLength(str);
}
//Size of str in main: 14
//Size of arr in function: 14
//Length of arr: 13
```

这段代码使用了模板函数`printSizeAndLength`，它接受一个数组引用作为参数。

在函数内部，使用`sizeof`计算数组大小时，数组不会退化为指针。

引用的作用就在于阻止拷贝的发生，通过传递引用，让形参得到和数组同样的地址。

