#include <iostream>
using std::cout;
using std::endl;

#include <string>

namespace MBase
{
    void *memmove(void *d, const void *s, size_t n)
    {
        if (!d || !s || n <= 0)
            return nullptr;

        if (d == s)
            return d;

        char *dest = (char *)d;
        const char *src = (char *)s;

        if (src < dest)
        {
            src += n;
            dest += n;
            while (n-- != 0)
            {
                *--dest = *--src;
            }
        }
        else
        {
            while (n-- != 0)
            {
                *dest++ = *src++;
            }
        }

        return dest;
    }
}

int main()
{
    std::string s{"hello"};
    static int len = s.length();
    char *dest = new char[len];
    MBase::memmove(dest, s.c_str(), len);

    cout << dest << endl;
}
