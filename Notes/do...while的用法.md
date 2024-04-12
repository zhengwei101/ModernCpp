# do...while 用法

## 1. `do...while`替换`goto`语句

```cpp
//最佳方案：do { if() break; if() break; } while(0)
do {
    // 步骤1
    ...
    if (步骤1失败) {
        break;
    }
    // 步骤2
    ...
    if (步骤2失败) {
        break;
    }
    // 步骤3
    ...
    if (步骤3失败) {
        break;
    }
} while(0);

// 步骤4
...
// 步骤5
...
//这个其实也适用于其他用do while的语言，不止C++
```

## 2. `do...while`在宏定义中的用法

```cpp
//使用 do {...} while(0)来包裹执行逻辑，可以保证宏定义函数执行的正确性，不会受到大括号、分号等的影响。
#define __set_task_state(tsk, state_value)      \
    do { (tsk)->state = (state_value); } while (0)
```
