#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
#include <vector>
#include <list>

#include <numeric> // std::accumulate
#include <iterator>
#include <functional>
#include <algorithm>

void test_vector()
{
    std::vector<int> vec{3,4,5,2,7};
    std::copy(begin(vec), end(vec), std::ostream_iterator<int>(cout, ", "));
    cout << " std::copy" << endl;

    std::stable_sort(begin(vec), end(vec), [](int a, int b) { return a < b;});
    cout << " std::stable_sort" << endl;

    std::for_each(begin(vec), end(vec), [](int val) { cout << val << " "; });
    cout << " std::for_each" << endl;

    int temp = 4;
    auto it = std::find_if(begin(vec), end(vec), [temp](int val) { return val > temp; });
    cout << *it << endl;
}

// 计算一个 vector 内所有数据之和
void get_collection_sum()
{
    std::vector<int> vNum{1, 2, 3, 4, 5};

    int sum = 0;
    
    // 手写循环遍历，不好
    for (const auto &v : vNum)
    {
        sum += v;
    }
    cout << "sum: " << sum << endl;

    // 使用标准库算法，代码简洁，意图清晰，表达力强。
    // 好
    auto new_sum = std::accumulate(begin(vNum), end(vNum), 0.0);
    cout << "use STL, sum: " << new_sum << endl;
};


int main()
{
    get_collection_sum();
}