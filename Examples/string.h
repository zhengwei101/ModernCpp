#pragma once

#include <cstring>
#include <iostream>


/**
 * 写类和类函数时，要注意的几个点：
 * 1. 在类的初始化列表中初始化成员变量。
 * 2. 类函数使用const来修饰。
 * 3. 类函数的参数，使用引用， 如果不会被修改，引用前增加const。
 * 4. 类函数的返回，使用引用，但注意，如果函数中返回的是临时变量，则不要返回引用，只能返回值。
 * 5. class存在pointer members时，必须有自定义的copy ctor(拷贝构造) 和 copy op=(赋值构造)，
 * 因为编译器默认的拷贝和赋值构造，用的是浅拷贝，只是简单拷贝指针的地址，而不是指针指向的值。
 */

class MString
{
public:
    MString(const char *pStr = nullptr);
    MString(const MString &mstr);
    MString& operator=(const MString &mstr);
     ~MString();
    char* get_c_str() const { return data_; }

private:
    char *data_ = nullptr; // 字符串是一个指针，指向一连串的字符，并以'\0'做为结尾。
};

inline MString::MString(const char *pStr)
{
    if (pStr)
    {
        data_ = new char[strlen(pStr) + 1];
        strcpy(data_, pStr);
    }
    else
    {
        data_ = new char[1];
        *data_ = '\0';
    }
}
inline MString::~MString()
{
    if (data_)
    {
        // array new (new char[]) 一定要搭配 array delete (delete [])
        delete[] data_; 
        data_ = nullptr;
    }
}

inline MString::MString(const MString &mstr)
{
    data_ = new char[strlen(mstr.data_) + 1];
    strcpy(data_, mstr.data_);
}

inline MString &
MString::operator=(const MString &mstr)
{
    if (this == &mstr) // 检测自我赋值(self assignment)
    {
        return *this;
    }
    delete[] data_;
    data_ = new char[strlen(mstr.data_) + 1];
    strcpy(data_, mstr.data_);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const MString &mstr)
{
    return os << mstr.get_c_str();
}