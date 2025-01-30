#ifndef KAD_STRING_H
#define KAD_STRING_H

#include <cstring>  // for strlen, strcpy, strcat
#include <iostream> // for std::ostream, std::istream

namespace kad {

class string {
private:
    char* data;   // 存储字符串的动态数组
    size_t len;   // 字符串长度（不包括 '\0'）

public:
    // 默认构造函数
    string() : data(new char[1]{'\0'}), len(0) {}

    // C 风格字符串构造
    string(const char* str) {
        len = std::strlen(str);
        data = new char[len + 1]; // 分配内存
        std::strcpy(data, str);
    }

    // 拷贝构造函数
    string(const string& other) {
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }

    // 移动构造函数
    string(string&& other) noexcept : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
    }

    // 析构函数
    ~string() {
        delete[] data;
    }

    // 拷贝赋值运算符
    string& operator=(const string& other) {
        if (this == &other) return *this;
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
        return *this;
    }

    // 移动赋值运算符
    string& operator=(string&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
        return *this;
    }

    // 获取字符串长度
    size_t size() const { return len; }

    // 获取 C 风格字符串
    const char* c_str() const { return data; }

    // 追加字符串
    void append(const string& other) {
        size_t new_len = len + other.len;
        char* new_data = new char[new_len + 1];
        std::strcpy(new_data, data);
        std::strcat(new_data, other.data);
        delete[] data;
        data = new_data;
        len = new_len;
    }

    // 清空字符串
    void clear() {
        delete[] data;
        data = new char[1]{'\0'};
        len = 0;
    }

    // 访问字符（支持修改）
    char& operator[](size_t index) { return data[index]; }

    // 访问字符（常量版本）
    const char& operator[](size_t index) const { return data[index]; }

    // 字符串相等比较
    bool operator==(const string& other) const {
        return std::strcmp(data, other.data) == 0;
    }

    // 拼接字符串
    string operator+(const string& other) const {
        string result(*this);
        result.append(other);
        return result;
    }

    // 流输出
    friend std::ostream& operator<<(std::ostream& os, const string& str) {
        os << str.data;
        return os;
    }

    // 流输入（读取单词，不支持空格）
    friend std::istream& operator>>(std::istream& is, string& str) {
        char buffer[1024]; // 预设缓冲区大小
        is >> buffer;      // 读取到缓冲区
        str = buffer;      // 赋值到 string 对象
        return is;
    }

    // 读取整行（支持空格）
    void getline(std::istream& is) {
        char buffer[1024];            // 预设缓冲区大小
        is.getline(buffer, sizeof(buffer)); // 读取整行
        *this = buffer;                // 赋值到 string 对象
    }
};

} // namespace kad

#endif // KAD_STRING_H
