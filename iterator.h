#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef> // for size_t, ptrdiff_t
#include <iostream>
#include <iterator> // for std::random_access_iterator_tag

namespace kad
{
    template <typename T>
    class iterator
    {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag; // 关键：声明为随机访问迭代器

        // 默认构造函数
        iterator() : ptr(nullptr) {}

        // 接受指针的构造函数
        explicit iterator(pointer p) : ptr(p) 
        {
            // std::cout << "iterator is start" << std::endl;
        }

        // 解引用操作符
        reference operator*() const { return *ptr; }

        // 指针访问
        pointer operator->() const { return ptr; }

        // 前置自增
        iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        // 后置自增
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // 前置自减
        iterator& operator--()
        {
            --ptr;
            return *this;
        }

        // 后置自减
        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // 加法运算
        iterator operator+(difference_type n) const { return iterator(ptr + n); }
        iterator& operator+=(difference_type n)
        {
            ptr += n;
            return *this;
        }

        // 减法运算
        iterator operator-(difference_type n) const { return iterator(ptr - n); }
        iterator& operator-=(difference_type n)
        {
            ptr -= n;
            return *this;
        }

        // 计算两个迭代器之间的距离
        difference_type operator-(const iterator &other) const { return ptr - other.ptr; }

        // 索引访问（新增）
        reference operator[](difference_type n) const { return *(ptr + n); }

        // 比较运算符
        bool operator<(const iterator &other) const { return ptr < other.ptr; }
        bool operator<=(const iterator &other) const { return ptr <= other.ptr; }
        bool operator>(const iterator &other) const { return ptr > other.ptr; }
        bool operator>=(const iterator &other) const { return ptr >= other.ptr; }
        bool operator==(const iterator &other) const { return ptr == other.ptr; }
        bool operator!=(const iterator &other) const { return ptr != other.ptr; }

        // 获取原始指针（用于非成员比较函数）
        pointer get() const { return ptr; }

    private:
        pointer ptr; // 指向元素的指针
    };

    // 允许直接与原始指针进行比较
    template <typename T>
    bool operator==(typename kad::iterator<T>::pointer ptr, const kad::iterator<T>& iter)
    {
        return ptr == iter.get();
    }

    template <typename T>
    bool operator!=(typename kad::iterator<T>::pointer ptr, const kad::iterator<T>& iter)
    {
        return ptr != iter.get();
    }

} // namespace kad

#endif // ITERATOR_H
