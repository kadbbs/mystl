#ifndef UNORDERED_MAP
#define UNORDERED_MAP


#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>

namespace kad {

template <typename KeyType, typename ValueType>
class unordered_map {
private:
    // 每个桶是一个链表，用于存储哈希冲突的元素
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t num_elements;
    float load_factor_threshold; // 负载因子阈值
    size_t capacity; // 当前桶的数量

    // 哈希函数
    size_t hash(const KeyType& key) const {
        // 使用 std::hash 作为默认哈希函数
        return std::hash<KeyType>{}(key) % capacity;
    }

    // 如果负载因子过大，进行扩容
    void rehash() {
        size_t new_capacity = capacity * 2;
        std::vector<std::list<std::pair<KeyType, ValueType>>> new_table(new_capacity);

        // 迁移元素到新的哈希表
        for (size_t i = 0; i < capacity; ++i) {
            for (auto& pair : table[i]) {
                size_t new_index = std::hash<KeyType>{}(pair.first) % new_capacity;
                new_table[new_index].push_back(std::move(pair));
            }
        }

        // 更新哈希表
        table = std::move(new_table);
        capacity = new_capacity;
    }

public:
    unordered_map(size_t initial_capacity = 16, float load_factor = 0.75)
        : capacity(initial_capacity), num_elements(0), load_factor_threshold(load_factor) {
        table.resize(capacity);
    }

    // 插入元素
    void insert(const KeyType& key, const ValueType& value) {
        if (num_elements >= capacity * load_factor_threshold) {
            rehash(); // 如果负载因子超过阈值，则扩容
        }

        size_t index = hash(key);
        auto& bucket = table[index];

        // 检查是否已存在该键，若存在则更新值
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        // 如果键不存在，则插入新元素
        bucket.push_back({key, value});
        ++num_elements;
    }

    // 查找元素
    ValueType& at(const KeyType& key) {
        size_t index = hash(key);
        auto& bucket = table[index];

        for (auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second; // 返回对应的值
            }
        }

        throw std::out_of_range("Key not found in unordered_map");
    }

    // 查找元素（const 版本）
    const ValueType& at(const KeyType& key) const {
        size_t index = hash(key);
        const auto& bucket = table[index];

        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second; // 返回对应的值
            }
        }

        throw std::out_of_range("Key not found in unordered_map");
    }

    // 判断某个键是否存在
    bool contains(const KeyType& key) const {
        size_t index = hash(key);
        const auto& bucket = table[index];

        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return true;
            }
        }

        return false;
    }

    // 返回元素数量
    size_t size() const {
        return num_elements;
    }

    // 返回容量（桶的数量）
    size_t bucket_count() const {
        return capacity;
    }

    // 输出 unordered_map（调试用）
    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            std::cout << std::endl;
        }
    }
};

} // namespace kad




#endif