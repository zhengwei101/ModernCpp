//13.6
#include<iostream>
#include<type_traits>
using namespace std;

struct A{
    int a;
    int f(int) { return 2011; }
};

enum E {
    e = 1,
};

union U {
    int u;
};

int main()
{
    cout << boolalpha << endl;
    cout << is_void<void>::value << endl;
    cout << is_integral<short>::value << endl;
    cout << is_floating_point<double>::value << endl;
    cout << is_array<int []>::value << endl;
    cout << is_pointer<int*>::value << endl;
    cout << is_null_pointer<nullptr_t>::value << endl;
    cout << is_member_object_pointer<int A::*>::value << endl;
    cout << is_member_function_pointer<int (A::*)(int)>::value << endl;
    cout << is_enum<E>::value << endl;
    cout << is_union<U>::value << endl;
    cout << is_class<string>::value<< endl;
    cout << is_function<int * (double)>::value << endl;
    cout << is_lvalue_reference<int&>::value << endl;
    cout << is_rvalue_reference<int&&>::value << endl;
    
}