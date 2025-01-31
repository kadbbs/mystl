#include <iostream>
#include "allocator.h"  // 包含自定义 allocator

int main()
{
    kad::allocator<int> alloc;

    // 分配内存
    int* p = alloc.allocate(3);

    // 使用 construct 构造对象
    alloc.construct(p, 10);          // 在 p 指向的内存位置构造一个值为 10 的 int
    alloc.construct(p + 1, 20);      // 在 p + 1 指向的内存位置构造一个值为 20 的 int
    alloc.construct(p + 2, 30);      // 在 p + 2 指向的内存位置构造一个值为 30 的 int

    // 输出构造的值
    std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;  // 输出 10 20 30

    // 销毁对象
    alloc.destroy(p);
    alloc.destroy(p + 1);
    alloc.destroy(p + 2);

    // 释放内存
    alloc.deallocate(p, 3);

    return 0;
}
