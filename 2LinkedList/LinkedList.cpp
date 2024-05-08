//
// Created by 高宇轩 on 2024/4/5.
//
#include "LinkedList.h"
#include <string>
#include <stdexcept>

/* 建立链表，创建哨兵节点 */
LinkedList::LinkedList() {
    sentinel = new ListNode(10086);
};
LinkedList::~LinkedList() {
    clear();
    delete sentinel;
};

/* 在链表尾部插入val元素 */
void LinkedList::append(int val) {
    ListNode* cur = sentinel;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = new ListNode(val);
}

/* 删除链表尾部的元素，并返回这个元素的值 */
int LinkedList::pop() {
    ListNode* prev = sentinel;
    ListNode* cur = sentinel->next;
    if (cur == nullptr) {
        throw std::out_of_range("LinkedList is empty");
    }

    while (cur->next != nullptr) {
        prev = cur;
        cur = cur->next;
    }
    int tmp = cur->value;
    prev->next = nullptr;
    delete cur;
    return tmp;
}

/* 删除第一个值为val的节点，如果没有值为val的节点，返回false并不修改原链表，否则返回true并修改 */
bool LinkedList::remove(int val) {
    ListNode* prev = sentinel;
    ListNode* cur = sentinel->next;
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
bool LinkedList::contains(int val) {
    ListNode* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value == val) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

/* 打印链表 */
void LinkedList::print() {
    if (sentinel->next == nullptr) {
        std::cout << "[]" << std::endl;
        return;
    }
    std::string res = "[";
    ListNode* cur = sentinel->next;
    while(cur != nullptr) {
        res += (std::to_string(cur->value) + ", ");
        cur = cur->next;
    }
    res.replace(res.size()-2, 2, "]");
    std::cout << res << std::endl;
}

/* 清除链表分配的空间 */
void LinkedList::clear() {
    ListNode* prev = sentinel;
    ListNode* cur = sentinel->next;
    while (cur != nullptr) {
        prev = cur;
        cur = cur->next;
        delete prev;
    }
    sentinel->next = nullptr;
}
