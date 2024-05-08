//
// Created by 高宇轩 on 2024/4/5.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H
#include <iostream>

struct ListNode{
    int value;
    ListNode* next;

    ListNode(): value(), next(nullptr) {};
    ListNode(int val) : value(val), next(nullptr) {};
};

class LinkedList{
private :
    ListNode* sentinel;

public:
    LinkedList();
    ~LinkedList();

    void append(int val);
    int pop();
    bool remove(int val);
    bool contains(int val);
    void print();
    void clear();
};

#endif //LINKEDLIST_LINKEDLIST_H
