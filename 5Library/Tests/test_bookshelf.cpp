//
// Created by 高宇轩 on 24-4-21.
//
#include "bookshelf.h"
#include <iostream>

int main() {
    bookshelf shelf;
    std::string id_1 = "1", id_2 = "2", id_3 = "3";
    std::string name_1 = "aaa", name_2 = "bbb", name_3 = "ccc";
    int num_1 = 9, num_2 = 8, num_3 = 7;
    shelf.add_book(id_1, name_1, num_1, num_1);
    shelf.add_book(id_2, name_2, num_2, num_2);
    shelf.add_book(id_3, name_3, num_3, num_3);
    std::cout << shelf.get_book_number() << std::endl;

    /* 本来是想要在bookshelf类中重写iterator的，现在这样做打破抽象隔离了，
     * 但是改了好久bug还是没写出来，只能先这样写了 */
    for (const auto &book_ptr: shelf.shelf) {
        std::cout << book_ptr->book_id << ", " << book_ptr->book_number << std::endl;
    }

    Book* book_1 = shelf.get_book(id_1, name_1);
    std::cout << book_1->book_id << ", " << book_1->book_name
        << ", " << book_1->book_number << std::endl;

    Book* book_2 = shelf.get_book(id_2, name_2);
    std::cout << book_2->book_id << ", " << book_2->book_name
              << ", " << book_2->book_number << std::endl;

    std::cout << shelf.delete_book(id_1, name_1) << std::endl;
    std::cout << shelf.delete_book(id_1, name_2) << std::endl;

    std::cout << shelf.get_book(id_1, name_1) << std::endl;
    std::cout << shelf.get_book(id_1, name_2) << std::endl;
    std::cout << shelf.get_book(id_2, name_2) << std::endl;

    return 0;


}
