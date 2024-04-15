# 区别

## strcpy和memcpy主要有以下3方面的区别

- 1，复制的内容不同。`strcpy`只能复制字符串，而`memcpy`可以复制任意内容，例如字符串，整型，结构体，类等。
- 2，复制的方法不同。`strcpy`不需要指定长度，它遇到被复制字符串的结束符'\0'才结束，所以容易溢出。`memcpy`则是根据其第3个参数决定复制的长度。
- 3，用途不同。通常在复制字符串时用`strcpy`, 而需要复制其他类型数据时则一般用`memcpy`。

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    char name[40];
    int age;
} person, person_copy;

int main()
{
    char myname[] = "Pierre de Fermat";

    memcpy(person.name, myname, strlen(myname) + 1);
    person.age = 46;

    memcpy(&person_copy, &person, sizeof(person));
    
    printf("person_copy: %s, %d\n", person_copy.name, person_copy.age);

    return 0;
}
```
