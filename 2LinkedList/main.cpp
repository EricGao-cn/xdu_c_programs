//
// Created by 高宇轩 on 2024/4/5.
//
#include "LinkedList.h"

int main() {
    LinkedList lst;
    lst.append(1);
    lst.append(2);
    lst.append(3);
    lst.append(4);
    lst.print();

    std::cout << "The last one of LinkedList is " << lst.pop() << std::endl;
    lst.print();

    std::cout << "Remove 2 from the LinkedList: " << lst.remove(2) << std::endl;
    lst.print();
    std::cout << "Remove 4 from the LinkedList: " << lst.remove(4) << std::endl;
    lst.print();

    std::cout << "The LinkedList contains 1: " << lst.contains(1) << std::endl;
    std::cout << "The LinkedList contains 2: " << lst.contains(2) << std::endl;

    lst.clear();
    std::cout << "After clear:";
    lst.print();

    return 0;
}