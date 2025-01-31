#ifndef KAD_STRING_H
#define KAD_STRING_H

#include <cstring>  // for strlen, strcpy, strcat
#include <iostream> // for std::ostream, std::istream

namespace kad
{
    
    template <typename T=char, typename alloc = kad::allocator<T>>
    class basechar
    {
    private:
        char *data; // 存储字符串的动态数组
        size_t len; // 字符串长度（不包括 '\0'）
        alloc allocator_;

    public:


        // 默认构造函数
        basechar() : data(allocator_.allocate(1)), len(0) {
            data[0]='\0';
        }

        // C 风格字符串构造
        basechar(const char *str)
        {
            len = std::strlen(str);
            data = allocator_.allocate(len+1); // 分配内存
            std::strcpy(data, str);
        }

        // 拷贝构造函数
        basechar(const basechar &other)
        {
            len = other.len;
            data = allocator_.allocate(len+1);
            std::strcpy(data, other.data);
        }

        // 移动构造函数
        basechar(basechar &&other) noexcept : data(other.data), len(other.len)
        {
            other.data = nullptr;
            other.len = 0;
        }

        // 析构函数
        ~basechar()
        {
            allocator_.deallocate(data,len+1);
        }

        // 拷贝赋值运算符
        basechar &operator=(const basechar &other)
        {
            if (this == &other)
                return *this;
            allocator_.deallocate(data,len+1);
            len = other.len;
            data = allocator_.allocate(len+1);
            std::strcpy(data, other.data);
            return *this;
        }

        // 移动赋值运算符
        basechar &operator=(basechar &&other) noexcept
        {
            if (this == &other)
                return *this;
            allocator_.deallocate(data,len+1);
            data = other.data;
            len = other.len;
            other.data = nullptr;
            other.len = 0;
            return *this;
        }

        // 获取字符串长度
        size_t size() const { return len; }

        // 获取 C 风格字符串
        const char *c_str() const { return data; }

        // 追加字符串
        void append(const basechar &other)
        {
            size_t new_len = len + other.len;
            char *new_data = allocator_.allocate(new_len + 1);
            std::strcpy(new_data, data);
            std::strcat(new_data, other.data);
            allocator_.deallocate(data,len+1);
            data = new_data;
            len = new_len;
        }

        // 清空字符串
        void clear()
        {
            allocator_.deallocate(data,len+1);
            data = allocator_.allocate(1);
            data[0]='\0';
            len = 0;
        }

        // 访问字符（支持修改）
        char &operator[](size_t index) { return data[index]; }

        // 访问字符（常量版本）
        const char &operator[](size_t index) const { return data[index]; }

        // 字符串相等比较
        bool operator==(const basechar &other) const
        {
            return std::strcmp(data, other.data) == 0;
        }

        // 拼接字符串
        basechar operator+(const basechar &other) const
        {
            basechar result(*this);
            result.append(other);
            return result;
        }
        basechar& operator+=(const basechar &other) 
        {

            append(other);
            return *this;
        }

        // 流输出
        friend std::ostream &operator<<(std::ostream &os, const basechar &str)
        {
            os << str.data;
            return os;
        }

        // 流输入（读取单词，不支持空格）
        friend std::istream &operator>>(std::istream &is, basechar &str)
        {
            char buffer[1024]; // 预设缓冲区大小
            is >> buffer;      // 读取到缓冲区
            str = buffer;      // 赋值到 string 对象
            return is;
        }

        // 读取整行（支持空格）
        void getline(std::istream &is)
        {
            char buffer[1024];                  // 预设缓冲区大小
            is.getline(buffer, sizeof(buffer)); // 读取整行
            *this = buffer;                     // 赋值到 string 对象
        }


        // 返回指向string首个元素的迭代器
        iterator<T> begin(){
            return iterator<T>(data);

        };
        // 返回指向string末尾元素之后位置的迭代器（尾后迭代器）
        iterator<T> end(){
            return iterator<T>(data+len);
        };

    T& front() 
    {
        if (len == 0) {
            throw std::out_of_range("vector::back(): empty vector");
        }

        return data[0];
    }

    T& back() 
    {
        if (len == 0) {
            throw std::out_of_range("vector::back(): empty vector");
        }

        return data[len-1];
    }



    };


    typedef basechar<> string;

} // namespace kad

#endif // KAD_STRING_H
