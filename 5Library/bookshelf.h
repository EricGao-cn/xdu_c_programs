//
// Created by 高宇轩 on 24-4-20.
//

#ifndef INC_5LIBRARY_BOOKSHELF_H
#define INC_5LIBRARY_BOOKSHELF_H
#include "LinkedList.h"
#include <string>
#include <utility>

typedef struct book {
    std::string book_id;
    std::string book_name;
    int book_number;
    int available_number;
    LinkedList<std::pair<std::string, std::string> > owner_info;

    book(std::string &id, std::string &name, int number, int available):
        book_id(id), book_name(name), book_number(number), available_number(available) {};
} Book;

class BookLinkedList : public LinkedList<Book*> {
public:
    /* 重写remove方法，便于直接删去id和name对应的图书 */
    bool remove(std::string &id, std::string &name);

    /* 重写get方法，便于直接得到id和name对应图书的指针 */
    Book* get(std::string &id, std::string &name);
};


class bookshelf {
private:
    int number_of_books{0};

public:
    BookLinkedList shelf;
    /* 新增书本信息 */
    void add_book(std::string &id, std::string &name, int number, int available);

    /* 删除书本信息，删除成功返回true */
    bool delete_book(std::string &id, std::string &name);

    /* 返回id和name对应的书籍，如果没找到返回nullptr */
    Book* get_book(std::string &id, std::string &name);

    /* 获取图书馆中书本数量 */
    int get_book_number() const;

};

#endif //INC_5LIBRARY_BOOKSHELF_H
