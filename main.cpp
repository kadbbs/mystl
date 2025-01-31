#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include "unordered_map.h"
#include <unordered_map>
int main()
{
    kad::unordered_map<std::string, int> umap;

    // 插入元素
    umap.insert("apple", 1);
    umap.insert("banana", 2);
    umap.insert("orange", 3);

    // 查找元素
    std::cout << "apple: " << umap.at("apple") << std::endl;
    std::cout << "banana: " << umap.at("banana") << std::endl;

    // 判断元素是否存在
    std::cout << "Contains 'grape': " << umap.contains("grape") << std::endl;

    // 输出哈希表内容
    umap.print();

    return 0;
}