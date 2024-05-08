//
// Created by 高宇轩 on 24-4-21.
//

#include "userlist.h"
#include "iostream"

int main() {
    userLists lst;

    std::string id_1 = "1", id_2 = "2", id_3 = "3";
    std::string name_1 = "aaa", name_2 = "bbb", name_3 = "ccc";
    int own_1 = 1, own_2 = 2, own_3 = 3;

    lst.add_user(id_1, name_1, own_1);
    lst.add_user(id_2, name_2, own_2);
    lst.add_user(id_3, name_3, own_3);
    std::cout << lst.get_user_number() << std::endl;

    User* user_1 = lst.get_user(id_1, name_1);
    User* user_0 = lst.get_user(id_2, name_3);
    User* user_3 = lst.get_user(id_3, name_3);

    for(const auto& user_ptr: lst.lst) {
        std::cout << user_ptr->user_id << ", " << user_ptr->user_name << ", " << user_ptr->owned_book_number << std::endl;
    }

    std::cout << user_1->user_id << ", " << user_1->user_name << std::endl;
    std::cout << user_0 << std::endl;
    std::cout << user_3->user_id << ", " << user_3->user_name << std::endl;

    std::cout << lst.delete_user(id_2, name_1) << std::endl;
    std::cout << lst.delete_user(id_2, name_2) << std::endl;

    std::cout << lst.get_user(id_1, name_2) << std::endl;
    std::cout << lst.get_user(id_2, name_2) << std::endl;



}