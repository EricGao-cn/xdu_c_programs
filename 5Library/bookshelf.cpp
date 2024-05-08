//
// Created by 高宇轩 on 24-4-20.
//

#include "bookshelf.h"

bool BookLinkedList::remove(std::string &id, std::string &name) {
    ListNode<Book*>* prev = sentinel;
    ListNode<Book*>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value->book_id == id && cur->value->book_name == name) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

Book* BookLinkedList::get(std::string &id, std::string &name) {
    ListNode<Book*>* cur = sentinel->next;
    while (cur != nullptr) {
        if (cur->value->book_id == id && cur->value->book_name == name) {
            return cur->value;
        }
        cur = cur->next;
    }
    return nullptr;
}

void bookshelf::add_book(std::string &id, std::string &name, int number, int available) {
    shelf.add(new Book{id, name, number, available});
    number_of_books += 1;
}

bool bookshelf::delete_book(std::string &id, std::string &name) {
    bool is_success = shelf.remove(id, name);
    if (is_success) {
        number_of_books -= 1;
    }
    return is_success;
}

Book* bookshelf::get_book(std::string &id, std::string &name) {
    return shelf.get(id, name);
}

int bookshelf::get_book_number() const {
    return number_of_books;
}
