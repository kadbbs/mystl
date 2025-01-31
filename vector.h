#ifndef VECTOR_H
#define VECTOR_H

#include "allocator.h"
#include "iterator.h"
#include <stdexcept>
namespace kad
{
    template <typename T, typename alloc = kad::allocator<T>>
    class vector
    {
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;

    private:
        using val_type = T;

    private:
        /* data */
        value_type *data_;
        size_type size_;
        size_type capacity_;
        alloc allocator_;

    public:
        vector(/* args */);
        vector(size_type n);
        vector(vector &vec);
        vector(vector &&vec);
        vector(size_type n, T val);
        ~vector();

    public:
        // 返回指向Vector首个元素的迭代器
        iterator<T> begin();
        // 返回指向Vector末尾元素之后位置的迭代器（尾后迭代器）
        iterator<T> end();
        void push_back(const val_type &value);
        size_t size() const;
        bool empty() const;
        value_type *data() const;

        T& back();
        T& front();



        T &operator[](size_t i)
        {
            return *(data_ + i);
        }
        T &operator=(vector &vec)
        {
            if(vec.data_==data){
                return *this;
            }

            vector<>
        }
    };

    template <typename T, typename alloc>
    iterator<T> vector<T, alloc>::begin()
    {
        return iterator<T>(data_);
    }

    template <typename T, typename alloc>
    iterator<T> vector<T, alloc>::end()
    {
        return iterator<T>(data_ + size_);
    }

    template <typename T, typename alloc>
    vector<T, alloc>::vector()
        : data_(nullptr), size_(0), capacity_(0), allocator_()
    {
        // 初始分配一些空间（例如，4个元素的空间）
        capacity_ = 4;
        data_ = allocator_.allocate(capacity_);
    }
    template <typename T, typename alloc>
    vector<T, alloc>::vector(size_type n)
        : data_(nullptr), size_(n), capacity_(n), allocator_()
    {
        // 初始分配一些空间n
        data_ = allocator_.allocate(capacity_);
    }

    template <typename T, typename alloc>
    vector<T, alloc>::vector(size_type n, T val)
        : data_(nullptr), size_(n), capacity_(n), allocator_()
    {
        // 初始分配一些空间n
        data_ = allocator_.allocate(capacity_);
        for (int i = 0; i < n; i++)
        {
            data_[i] = val;
        }
    }

    template <typename T, typename alloc>
    vector<T, alloc>::~vector()
    {
        // 释放已分配的内存
        allocator_.deallocate(data_, capacity_);
    }

    template <typename T, typename alloc>
    void vector<T, alloc>::push_back(const val_type &value)
    {
        if (size_ == capacity_)
        {
            // 如果当前大小等于容量，增加容量（例如，翻倍）
            size_t new_capacity = capacity_ * 2;
            val_type *new_data = allocator_.allocate(new_capacity);

            // 复制旧数据到新数据区域
            for (size_t i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }

            // 释放旧数据区域
            allocator_.deallocate(data_, capacity_);

            // 更新数据指针和容量
            data_ = new_data;
            capacity_ = new_capacity;
        }

        // 在末尾添加新元素
        data_[size_] = value;
        ++size_;
    }

    template <typename T, typename alloc>
    size_t vector<T, alloc>::size() const
    {
        return size_;
    }

    template <typename T, typename alloc>
    bool vector<T, alloc>::empty() const
    {
        return size_ == 0;
    }

    template <typename T, typename alloc>
    typename vector<T, alloc>::value_type *vector<T, alloc>::data() const
    {
        return data_;
    }


    template <typename T, typename alloc>
    T& vector<T, alloc>::front() 
    {
        if (size_ == 0) {
            throw std::out_of_range("vector::back(): empty vector");
        }

        return data_[0];
    }

        template <typename T, typename alloc>
    T& vector<T, alloc>::back() 
    {
        if (size_ == 0) {
            throw std::out_of_range("vector::back(): empty vector");
        }

        return data_[size_-1];
    }



}

#endif