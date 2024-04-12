#include <iostream>
#include <locale>

void PrintWchar(bool bSetGlobalLocale)
{
    std::locale lc_old;

    if (bSetGlobalLocale)
    {
        try
        {
            // 设置全局locale为中文，并记录返回值，即原来的全局locale
            lc_old = std::locale::global(std::locale("zh_CN"));
        }
        catch (std::runtime_error &e)
        {
            // 在我本机用mingw64编译会报错(_S_create_c_locale name not valid)，用LLVM则正常
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
    }
    std::cout << "abc" << std::endl;
    std::wcout << L"output English\n";
    std::wcout << L"输出一句中文\n";
    std::cout << "now-wcout: " << std::wcout.getloc().name() << std::endl;
    std::locale lc_global;
    std::cout << "now-global: " << lc_global.name() << std::endl;

    if(bSetGlobalLocale)
    {
        // 设回原来的全局locale
        std::locale::global(lc_old);
    }
}

void test_imbue()
{
    std::cout << "cout: " << std::cout.getloc().name() << "\n";
    std::cout << "wcout: " << std::wcout.getloc().name() << "\n";

    std::wcout.imbue(std::locale("zh_CN"));
    std::wcout << L"你好，世界" << std::endl;

    std::cout << "cout: " << std::cout.getloc().name() << "\n";
    std::cout << "wcout: " << std::wcout.getloc().name() << "\n";
}

int main()
{
    PrintWchar(true);

    test_imbue();

    PrintWchar(false);
}
