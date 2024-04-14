# `std::local`的用法

> 示例代码，Examples/locale_test.cpp

## 全域 locale

所谓全域 locale，就是流对象不使用`imbue()`方法来指定locale，相当于C标准库中的`setlocale()`设定的 locale

程式初始化时，全域 locale 为 `C` locale

设定全域locale为环境设定的`C` locale

```c++
//相当于 setlocale(LC_ALL, "");
std::locale::global(std::locale(""));
```

## locale 对象方法

- std::string name() const  返回locale的名称
  
```c++
locale lc;
cout << "Current global locale is: " << lc.name() << endl;
```

注意，name()返回的是std::string对象，

而std::wostream 的 `<<` 操作在std::string是无定义的，所以这样写会出错，`wcout << lc.name();`，

除非自己重载`std::wostream`的`<<`操作符。

## 使用`std::wcout`流对象和`std::locale`对象，输出`wchar_t`字符串

```c++
void PrintWchar()
{
    try
    {
        //设置全局locale为中文，并记录返回值，即原来的全局locale
        std::locale lc_old = std::locale::global(std::locale("zh_CN"));  
    } 
    catch (std::runtime_error& e)
    {
        //在我本机用mingw64编译会报错，用LLVM则正常
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    std::wcout << L"output English\n";
    std::wcout << L"输出一句中文\n";
    std::cout << "now-wcout: " << std::wcout.getloc().name() << std::endl;
    std::locale lc_global;
    std::cout << "now-global: " << lc_global.name() << std::endl;
    //设回原来的全局locale
    std::locale::global(lc_old);  
}
```

## 使用'std::wcout.imbue()`设置locale

```c++
    std::wcout.imbue(std::locale("zh_CN"));
    std::wcout << L"你好，世界" << std::endl;
```

## 解决`std::cout` 输出中文乱码

### 方法1. 通过system命令修改编码

```c++
#include <iostream>
int main()
{
    system("chcp 65001");
    std::cout << "你好，世界" << std::endl;
}
```

### 方法2. 命令行执行`chcp`命令

```bash
chcp 65001
```

### 方法3， 通过SetConsoleOutputCP函数修改编码

```c++
#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "你好，世界" << std::endl;
}
```
