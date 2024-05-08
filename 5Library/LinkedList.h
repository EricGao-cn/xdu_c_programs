//
// Created by 高宇轩 on 24-4-20.
//

#ifndef LIBSIM_LINKEDLIST_H
#define LIBSIM_LINKEDLIST_H

template <typename T>
struct ListNode {
    T value;
    ListNode* next;

    ListNode(): value(), next(nullptr) {};
    explicit ListNode(T val) : value(val), next(nullptr) {};
};

template <typename T>
class LinkedList{

protected:
    ListNode<T>* sentinel;
public:
    LinkedList();
    ~LinkedList();

    void add(T val);
    bool remove(T val);
    T get(T val);
    void clear();

    /* Iterator类，使链表能够迭代 */
    class Iterator {
    private:
        ListNode<T>* current;

    public:
        Iterator(ListNode<T>* current) : current(current) {}

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() {
            return current->value;
        }
    };

    Iterator begin() {
        return Iterator(sentinel->next);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
};

/* 模板函数是要写在.h文件里的，因为不知道目标的数据类型，所以在.cpp文件中是不会编译的 */
template <typename T>
LinkedList<T>::LinkedList() {
    sentinel = new ListNode<T>();
};

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
    delete sentinel;
};

/* 在链表尾部插入val元素 */
template <typename T>
void LinkedList<T>::add(T val) {
    ListNode<T>* cur = sentinel;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new ListNode<T>(val);
}

/* 删除第一个值为val的节点，如果没有值为val的节点，返回false并不修改原链表，否则返回true并修改 */
template <typename T>
bool LinkedList<T>::remove(T val) {
    ListNode<T>* prev = sentinel;
    ListNode<T>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

/* 判断链表中是否存在值为val的节点 */
template <typename T>
T LinkedList<T>::get(T val) {
    ListNode<T>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            return cur->value;
        }
        cur = cur->next;
    }
    return nullptr;
}

/* 释放所有内存，用在折构函数中 */
template <typename T>
void LinkedList<T>::clear() {
    ListNode<T>* prev;
    ListNode<T>* cur = sentinel->next;
    while (cur != nullptr) {
        prev = cur;
        cur = cur->next;
        delete prev;
    }
    sentinel->next = nullptr;
}
#endif //LIBSIM_LINKEDLIST_H
