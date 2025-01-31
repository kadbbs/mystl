#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory>  // for std::allocator
#include <iterator>  // for std::iterator, std::advance
#include "allocator.h"

namespace kad {

    // 链表节点
    template <typename T>
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    // 双向链表实现
    template <typename T, typename Allocator = kad::allocator<Node<T>>>
    class list {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size_;
        Allocator allocator_;

        // 通过分配器创建节点
        Node<T>* create_node(const T& value) {
            Node<T>* node = allocator_.allocate(1);
            allocator_.construct(node, value);
            return node;
        }

        // 通过分配器销毁节点
        void destroy_node(Node<T>* node) {
            allocator_.destroy(node);
            allocator_.deallocate(node, 1);
        }

    public:
        // 构造函数
        list() : head(nullptr), tail(nullptr), size_(0) {}

        // 析构函数
        ~list() {
            clear();
        }

        // 插入到链表尾部
        void push_back(const T& value) {
            Node<T>* new_node = create_node(value);
            if (tail) {
                tail->next = new_node;
                new_node->prev = tail;
            } else {
                head = new_node;
            }
            tail = new_node;
            ++size_;
        }

        // 插入到链表头部
        void push_front(const T& value) {
            Node<T>* new_node = create_node(value);
            if (head) {
                head->prev = new_node;
                new_node->next = head;
            } else {
                tail = new_node;
            }
            head = new_node;
            ++size_;
        }

        // 在指定位置插入元素
        void insert(size_t index, const T& value) {
            if (index > size_) {
                throw std::out_of_range("Index out of range");
            }

            if (index == 0) {
                push_front(value);
                return;
            }

            if (index == size_) {
                push_back(value);
                return;
            }

            Node<T>* new_node = create_node(value);
            Node<T>* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }

            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;

            ++size_;
        }

        // 删除链表头部
        void pop_front() {
            if (head) {
                Node<T>* temp = head;
                head = head->next;
                if (head) {
                    head->prev = nullptr;
                } else {
                    tail = nullptr;
                }
                destroy_node(temp);
                --size_;
            }
        }

        // 删除链表尾部
        void pop_back() {
            if (tail) {
                Node<T>* temp = tail;
                tail = tail->prev;
                if (tail) {
                    tail->next = nullptr;
                } else {
                    head = nullptr;
                }
                destroy_node(temp);
                --size_;
            }
        }

        // 获取链表大小
        size_t size() const {
            return size_;
        }

        // 判断链表是否为空
        bool empty() const {
            return size_ == 0;
        }

        // 清空链表
        void clear() {
            while (head) {
                pop_front();
            }
        }

        // 迭代器支持
        class iterator {
        private:
            Node<T>* current;

        public:
            iterator(Node<T>* node) : current(node) {}

            T& operator*() {
                return current->data;
            }

            iterator& operator++() {
                current = current->next;
                return *this;
            }

            iterator& operator--() {
                current = current->prev;
                return *this;
            }

            bool operator!=(const iterator& other) const {
                return current != other.current;
            }
        };

        // 返回链表的开始迭代器
        iterator begin() {
            return iterator(head);
        }

        // 返回链表的结束迭代器
        iterator end() {
            return iterator(nullptr);
        }

        // 输出链表的内容
        void print() const {
            Node<T>* current = head;
            while (current) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    };
}




#endif