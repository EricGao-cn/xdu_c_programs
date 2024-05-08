//
// Created by 高宇轩 on 24-4-21.
//
#include "LinkedList.h"
#include "iostream"

int main() {
    LinkedList<int*> lst;
    int a = 1, b = 2, c = 3;
    lst.add(&a);
    lst.add(&b);
    lst.add(&c);

    for (const auto &i: lst) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << *(lst.get(&b)) << std::endl;
    lst.remove(&b);
    std::cout << lst.get(&b) << std::endl;

    return 0;

}