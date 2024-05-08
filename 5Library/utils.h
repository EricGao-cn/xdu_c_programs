//
// Created by 高宇轩 on 24-4-21.
//

#ifndef LIBSIM_UTILS_H
#define LIBSIM_UTILS_H

#include "bookshelf.h"
#include "userlist.h"
#include <iostream>
#include <fstream>

bool load_info(bookshelf &BookShelf, userLists &UserLists);
void save_info(bookshelf &BookShelf, userLists &UserLists);
bool load_from_books_info(bookshelf &BookShelf);
bool load_from_users_info(userLists &UserLists);
bool load_from_borrow_info(bookshelf &BookShelf, userLists &UserLists);
void save_to_books_info(bookshelf &BookShelf);
void save_to_users_info(userLists &UserLists);
void save_to_borrow_info(bookshelf &BookShelf);


void admin_action(bookshelf &BookShelf, userLists &UserLists);
void display_admin_menu();
void admin_add_book(bookshelf &BookShelf);
void admin_modify_book(bookshelf &BookShelf);
void admin_delete_book(bookshelf &BookShelf);
void admin_add_user(userLists &UserLists);
void admin_modify_user(userLists &UserLists);
void admin_delete_user(userLists &UserLists);
void admin_look_up_book_information(bookshelf &BookShelf);
void admin_look_up_user_information(userLists &UserLists);

void user_action(bookshelf &BookShelf, userLists &UserLists, std::string &user_name);
void display_user_menu();
void user_borrow_book(bookshelf &BookShelf, userLists &UserLists, std::string &user_name);
void user_return_book(bookshelf &BookShelf, userLists &UserLists, std::string &user_name);
void user_look_up_book_info(bookshelf &BookShelf);
void user_look_up_borrow_info(userLists &UserLists, std::string &user_name);

#endif //LIBSIM_UTILS_H
