#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>  // for size_t, ptrdiff_t
#include <new>      // for std::bad_alloc, ::operator new, ::operator delete
#include <stdexcept> // for std::out_of_range
namespace kad
{
    template <typename T>
    class allocator
    {
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;

        allocator() = default;
        ~allocator() = default;

        // 分配内存
        T* allocate(size_type n)
        {
            if (n > static_cast<size_type>(-1) / sizeof(T))
            {
                throw std::bad_alloc(); // 如果请求的内存大小太大，则抛出异常
            }
            T* p = static_cast<T*>(::operator new(n * sizeof(T))); // 调用 ::operator new 分配内存
            if (!p)
            {
                throw std::bad_alloc(); // 如果分配失败，抛出 std::bad_alloc 异常
            }
            return p;
        }

        // 释放内存
        void deallocate(T* p, size_type n)
        {
            ::operator delete(p, n * sizeof(T)); // 调用 ::operator delete 释放内存
        }

        // 在已分配内存上构造对象
        void construct(T* p, const T& value)
        {
            new(p) T(value); // 在 p 指向的内存位置上构造一个 T 对象，使用复制构造函数
        }

        // 销毁对象
        void destroy(T* p)
        {
            p->~T(); // 显式调用对象的析构函数
        }
    };
}
#endif // ALLOCATOR_H
