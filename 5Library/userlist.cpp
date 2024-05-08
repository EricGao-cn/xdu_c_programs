//
// Created by 高宇轩 on 24-4-20.
//

#include "userlist.h"

bool UserLinkedList::remove(std::string &id, std::string &name) {
    ListNode<User*>* prev = sentinel;
    ListNode<User*>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value->user_id == id && cur->value->user_name == name) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

User* UserLinkedList::get(std::string &id, std::string &name) {
    ListNode<User*>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value->user_id == id && cur->value->user_name == name) {
            return cur->value;
        }
        cur = cur->next;
    }
    return nullptr;
}

void userLists::add_user(std::string &id, std::string &name, int owning_num) {
    lst.add(new User(id, name, owning_num));
    number_of_users += 1;
}

bool userLists::delete_user(std::string &id, std::string &name) {
    bool is_success = lst.remove(id, name);
    if (is_success) {
        number_of_users -= 1;
    }
    return is_success;
}

User* userLists::get_user(std::string &id, std::string &name) {
    return lst.get(id, name);
}

int userLists::get_user_number() const {
    return number_of_users;
}
