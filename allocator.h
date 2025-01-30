// allocator.h
#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef> // for size_t, ptrdiff_t
#include <new>     // for std::bad_alloc, ::operator new, ::operator delete
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
        // 声明 allocate 方法
        T *allocate(size_type n)
        {
            if (n > static_cast<size_type>(-1) / sizeof(T))
            {
                throw std::bad_alloc(); // 如果分配大小过大，抛出异常
            }
            return static_cast<T *>(::operator new(n * sizeof(T)));
        };
        // 通常还需要一个 deallocate 方法来释放内存
        void deallocate(T *p, size_type n)
        {
            ::operator delete(p, n * sizeof(T));
        };
    };
}
#endif // ALLOCATOR_H