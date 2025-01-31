#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <utility>  // for std::pair

namespace kad {

    // 哈希表中的桶结构，使用链表解决哈希冲突
    template <typename Key, typename T>
    class map {
    private:
        // 哈希表每个桶存储一对键值对
        std::vector<std::list<std::pair<Key, T>>> table;
        size_t num_elements;
        size_t bucket_count;

        // 哈希函数（简单取余）
        size_t hash(const Key& key) const {
            return std::hash<Key>{}(key) % bucket_count;
        }

    public:
        // 构造函数
        map(size_t initial_bucket_count = 16) 
            : bucket_count(initial_bucket_count), num_elements(0) {
            table.resize(bucket_count);
        }

        // 插入键值对
        void insert(const Key& key, const T& value) {
            size_t index = hash(key);
            auto& bucket = table[index];

            // 查找是否已存在相同的键
            for (auto& pair : bucket) {
                if (pair.first == key) {
                    pair.second = value; // 更新值
                    return;
                }
            }

            // 否则插入新的键值对
            bucket.push_back(std::make_pair(key, value));
            ++num_elements;
        }

        // 查找键值对
        T* find(const Key& key) {
            size_t index = hash(key);
            auto& bucket = table[index];

            for (auto& pair : bucket) {
                if (pair.first == key) {
                    return &pair.second;
                }
            }

            return nullptr;  // 未找到
        }

        // 删除键值对
        void erase(const Key& key) {
            size_t index = hash(key);
            auto& bucket = table[index];

            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->first == key) {
                    bucket.erase(it);
                    --num_elements;
                    return;
                }
            }
        }

        // 获取元素数量
        size_t size() const {
            return num_elements;
        }

        // 判断 map 是否为空
        bool empty() const {
            return num_elements == 0;
        }

        // 迭代器支持
        auto begin() {
            for (size_t i = 0; i < bucket_count; ++i) {
                if (!table[i].empty()) {
                    return table[i].begin();
                }
            }
            return table[0].end();
        }

        auto end() {
            return table[0].end();
        }
    };
}

#endif