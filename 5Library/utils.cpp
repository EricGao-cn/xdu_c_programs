//
// Created by 高宇轩 on 24-4-20.
//
#include "utils.h"

/* 从数据库中读取所有数据 */
bool load_info(bookshelf &BookShelf, userLists &UserLists) {
    return load_from_books_info(BookShelf)
    && load_from_users_info(UserLists)
    && load_from_borrow_info(BookShelf, UserLists);
}

/* 将所有数据写入数据库 */
void save_info(bookshelf &BookShelf, userLists &UserLists) {
    save_to_books_info(BookShelf);
    save_to_users_info(UserLists);
    save_to_borrow_info(BookShelf);
}

/* 读取books_info中的数据 */
bool load_from_books_info(bookshelf &BookShelf) {
    std::fstream inputFile("database/books_info.txt");
    if (!inputFile) {
        std::cout << "Fail to open books_info.txt" << std::endl;
        return false;
    }
    std::string id, name;
    int num, available;
    while (inputFile >> id >> name >> num >> available) {
        BookShelf.add_book(id, name, num, available);
    }

    inputFile.close();
    return true;
}

/* 读取users_info中的数据 */
bool load_from_users_info(userLists &UserLists) {
    std::fstream inputFile("database/users_info.txt");
    if (!inputFile) {
        std::cout << "Fail to open users_info.txt" << std::endl;
        return false;
    }
    std::string id, name;
    int num;
    while (inputFile >> id >> name >> num) {
        UserLists.add_user(id, name, num);
    }

    inputFile.close();
    return true;
}

/* 读取borrow_info中的数据 */
bool load_from_borrow_info(bookshelf &BookShelf, userLists &UserLists) {
    std::fstream inputFile("database/borrow_info.txt");
    if (!inputFile) {
        std::cout << "Fail to open borrow_info.txt" << std::endl;
        return false;
    }
    std::string book_id, book_name, user_id, user_name;
    while (inputFile >> book_id >> book_name >> user_id >> user_name) {
        Book* book_ptr = BookShelf.get_book(book_id, book_name);
        User* user_ptr = UserLists.get_user(user_id, user_name);
        if (book_ptr == nullptr) {
            std::cout << "The book with id: " << book_id
                      << " and name: " << book_name << " doesn't exist." << std::endl;
            return false;
        }
        if (user_ptr == nullptr) {
            std::cout << "The user named " << user_name << " with ID"
                      << user_id << " doesn't exist." << std::endl;
            return false;
        }
        if (book_ptr->available_number == 0) {
            std::cout << "The book with id: " << book_id << " and name: "
                      << book_name << " have all been borrowed" << std::endl;
            return false;
        }
        book_ptr->available_number -= 1;
        (book_ptr->owner_info).add(std::make_pair(user_id, user_name));

        user_ptr->owned_book_number += 1;
        (user_ptr->owning_info).add(std::make_pair(book_id, book_name));
    }

    inputFile.close();
    return true;
}

/* 写入books_info中的数据 */
void save_to_books_info(bookshelf &BookShelf) {
    std::ofstream outputFile("database/books_info.txt");
    for (const auto& book_ptr: BookShelf.shelf) {
        outputFile << book_ptr->book_id << " " << book_ptr->book_name << " "
                   << book_ptr->book_number << " " << book_ptr->available_number << std::endl;
    }

    outputFile.close();
}

/* 写入users_info中的数据 */
void save_to_users_info(userLists &UserLists) {
    std::ofstream outputFile("database/users_info.txt");
    for (const auto& user_ptr : UserLists.lst) {
        outputFile << user_ptr->user_id << " " << user_ptr->user_name << " "
                   << user_ptr->owned_book_number << std::endl;
    }

    outputFile.close();
}

/* 写入borrows_info中的数据 */
void save_to_borrow_info(bookshelf &BookShelf) {
    std::ofstream outputFile("database/borrow_info.txt");
    for (const auto& book_ptr: BookShelf.shelf) {
        auto info_list = book_ptr->owner_info;
        for (const auto& owner_pair: info_list) {
            outputFile << book_ptr->book_id << " " << book_ptr->book_name << " "
                       << owner_pair.first << " " << owner_pair.second << std::endl;
        }
    }

    outputFile.close();
}

/* 管理员的操作 */
void admin_action(bookshelf &BookShelf, userLists &UserLists) {
    display_admin_menu();
    load_info(BookShelf, UserLists);
    int option;
    while (std::cin >> option) {
        switch (option) {
            case 0:
                break;
            case 1:
                admin_add_book(BookShelf);
                break;
            case 2:
                admin_modify_book(BookShelf);
                break;
            case 3:
                admin_delete_book(BookShelf);
                break;
            case 4:
                admin_add_user(UserLists);
                break;
            case 5:
                admin_modify_user(UserLists);
                break;
            case 6:
                admin_delete_user(UserLists);
                break;
            case 7:
                admin_look_up_book_information(BookShelf);
                break;
            case 8:
                admin_look_up_user_information(UserLists);
                break;
            default:
                std::cout << "Invalid request, please type again" << std::endl;
                break;
        }

        if (option == 0) {
            break;
        } else {
            display_admin_menu();
        }
    }
    std::cout << "Please wait to save the data. " << std::endl;
    save_info(BookShelf, UserLists);
    std::cout << "Have a nice day! GoodBye :)" << std::endl;
}

/* 显示管理员操作菜单 */
void display_admin_menu() {
    std::cout << std::endl;
    std::cout << "............................................................" << std::endl;
    std::cout << ".                   ADMINISTRATOR MENU                     ." << std::endl;
    std::cout << ". Please enter the number for the corresponding operation  ." << std::endl;
    std::cout << ". 0) Logout                                                ." << std::endl;
    std::cout << ". 1) Input book information                                ." << std::endl;
    std::cout << ". 2) Modify book information                               ." << std::endl;
    std::cout << ". 3) Delete book information                               ." << std::endl;
    std::cout << ". 4) Input user information                                ." << std::endl;
    std::cout << ". 5) Modify user information                               ." << std::endl;
    std::cout << ". 6) Delete user information                               ." << std::endl;
    std::cout << ". 7) Look up book information                              ." << std::endl;
    std::cout << ". 8) Look up users' borrow information                     ." << std::endl;
    std::cout << "............................................................" << std::endl;
    std::cout << std::endl;
}

/* 管理员录入书籍信息 */
void admin_add_book(bookshelf &BookShelf) {
    std::cout << "Input the information of the new book with format: book_id book_name book_number" << std::endl;
    std::cout << "For example: 12345 Book_and_book 5" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::string id, name;
    int num;
    std::cin >> id >> name >> num;
    BookShelf.add_book(id, name, num, num);
    std::cout << "Success! id: " << id << " name: " << name << " number:" << num << std::endl;
}

/* 管理员修改书籍信息 */
void admin_modify_book(bookshelf &BookShelf) {
    std::cout << "Input the id and name of book in the system" << std::endl;
    std::cout << "For example: 12345 Book_and_book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;
    std::string id, name;
    std::cin >> id >> name;

    std::cout << "Choose which info you want to change: 0. quit  1. book_id  2. book_name  3. book_number" << std::endl;
    std::cout << "Then input the new information" << std::endl;
    std::cout << "For example: 2 Book_Book_Book" << std::endl;
    std::cout << std::endl;

    Book* book_ptr = BookShelf.get_book(id, name);
    int option;
    std::string change_to;
    std::cin >> option >> change_to;
    switch (option) {
        case 0:
            return;
        case 1:
            book_ptr->book_id = change_to;
            std::cout << "Success!" << std::endl;
            break;
        case 2:
            book_ptr->book_name = change_to;
            std::cout << "Success!" << std::endl;
            break;
        case 3:
            if (std::stoi(change_to) < book_ptr->book_number - book_ptr->available_number) {
                std::cout << "Incorrect modification." << std::endl;
                return;
            }
            book_ptr->available_number = book_ptr->available_number + std::stoi(change_to) - book_ptr->book_number;
            book_ptr->book_number = std::stoi(change_to);
            std::cout << "Success" << std::endl;
            break;
        default:
            std::cout << "Invalid request" << std::endl;
            break;
    }
}

/* 管理员删除书籍信息 */
void admin_delete_book(bookshelf &BookShelf) {
    std::cout << "Input the id and name of book you want to delete" << std::endl;
    std::cout << "For example: 12345 Book_and_book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;
    std::string id, name;
    std::cin >> id >> name;

    bool is_success = BookShelf.delete_book(id, name);
    if (!is_success) {
        std::cout << "Fail to delete the book, check your input." << std::endl;
    } else {
        std::cout << "Successfully delete the book. " << std::endl;
    }
}

/* 管理员录入用户信息 */
void admin_add_user(userLists &UserLists) {
    std::cout << "Input the information of the new user with format: user_id user_book" << std::endl;
    std::cout << "For example: 12345 User_and_user" << std::endl;
    std::cout << "Attention: If there is space in the user_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::string id, name;
    std::cin >> id >> name;
    UserLists.add_user(id, name, 0);
    std::cout << "Success! id: " << id << " name: " << name << std::endl;
}

/* 管理员修改用户信息 */
void admin_modify_user(userLists &UserLists) {
    std::cout << "Input the id and name of user in the system" << std::endl;
    std::cout << "For example: 12345 User_and_User" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;
    std::string id, name;
    std::cin >> id >> name;

    std::cout << "Choose which info you want to change: 0. quit  1. user_id  2. user_name " << std::endl;
    std::cout << "Then input the new information" << std::endl;
    std::cout << "For example: 2 User_and_User" << std::endl;

    User* user_ptr = UserLists.get_user(id, name);
    int option;
    std::string change_to;
    std::cin >> option >> change_to;
    switch (option) {
        case 0:
            return;
        case 1:
            user_ptr->user_id = change_to;
            std::cout << "Success!" << std::endl;
            break;
        case 2:
            user_ptr->user_name = change_to;
            std::cout << "Success!" << std::endl;
            break;
        default:
            std::cout << "Invalid request" << std::endl;
            break;
    }
}

/* 管理员删除用户信息 */
void admin_delete_user(userLists &UserLists) {
    std::cout << "Input the id and name of user you want to delete" << std::endl;
    std::cout << "For example: 12345 User_and_User" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;
    std::string id, name;
    std::cin >> id >> name;

    bool is_success = UserLists.delete_user(id, name);
    if (!is_success) {
        std::cout << "Fail to delete the user, check your input." << std::endl;
    } else {
        std::cout << "Successfully delete the user. " << std::endl;
    }
}

/* 管理员查阅书籍信息 */
void admin_look_up_book_information(bookshelf &BookShelf) {
    std::cout << "Input the id and name of book you want to look up" << std::endl;
    std::cout << "For example: 12345 Book_and_Book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::string id, name;
    std::cin >> id >> name;
    Book* book_ptr = BookShelf.get_book(id, name);
    if (book_ptr == nullptr) {
        std::cout << "The book doesn't exist, please check your input info" << std::endl;
    } else {
        std::cout << "Book ID:          " << book_ptr->book_id << std::endl;
        std::cout << "Book Name:        " << book_ptr->book_name << std::endl;
        std::cout << "Book Number:      " << book_ptr->book_number << std::endl;
        std::cout << "Available Number: " << book_ptr->available_number << std::endl;
        std::cout << "Borrow information: " << std::endl;

        int enumerate = 1;
        for(const auto &borrow_pair:book_ptr->owner_info) {
            std::cout << enumerate << ") " << borrow_pair.first << " " << borrow_pair.second << std::endl;
            enumerate += 1;
        }
    }
}

/* 管理员查询用户信息 */
void admin_look_up_user_information(userLists &UserLists) {
    std::cout << "Input the id and name of user you want to look up" << std::endl;
    std::cout << "For example: 12345 User_and_User" << std::endl;
    std::cout << "Attention: If there is space in the user_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::string id, name;
    std::cin >> id >> name;
    User* user_ptr = UserLists.get_user(id, name);
    if (user_ptr == nullptr) {
        std::cout << "The user doesn't exist, please check your input info" << std::endl;
    } else {
        std::cout << "User ID:          " << user_ptr->user_id << std::endl;
        std::cout << "User Name:        " << user_ptr->user_name << std::endl;
        std::cout << "Borrow Number:    " << user_ptr->owned_book_number << std::endl;
        std::cout << "Borrow information: " << std::endl;

        int enumerate = 1;
        for (const auto &borrow_pair: user_ptr->owning_info) {
            std::cout << enumerate << ") " << borrow_pair.first << " " << borrow_pair.second << std::endl;
            enumerate += 1;
        }
    }
}

/* 用户操作 */
void user_action(bookshelf &BookShelf, userLists &UserLists, std::string &name) {
    display_user_menu();
    load_info(BookShelf, UserLists);
    int option;
    while (std::cin >> option) {
        switch (option) {
            case 0:
                break;
            case 1:
                user_borrow_book(BookShelf, UserLists, name);
                break;
            case 2:
                user_return_book(BookShelf, UserLists, name);
                break;
            case 3:
                user_look_up_book_info(BookShelf);
                break;
            case 4:
                user_look_up_borrow_info(UserLists, name);
                break;
            default:
                std::cout << "Invalid request, please type again" << std::endl;
                break;
        }

        if (option == 0) {
            break;
        } else {
            display_user_menu();
        }
    }
    std::cout << "Please wait to save the data. " << std::endl;
    save_info(BookShelf, UserLists);
    std::cout << "Have a nice day! GoodBye :)" << std::endl;
}

/* 显示用户选择界面 */
void display_user_menu() {
    std::cout << std::endl;
    std::cout << "............................................................" << std::endl;
    std::cout << ".                         USER MENU                        ." << std::endl;
    std::cout << ". Please enter the number for the corresponding operation  ." << std::endl;
    std::cout << ". 0) Logout                                                ." << std::endl;
    std::cout << ". 1) Borrow book                                           ." << std::endl;
    std::cout << ". 2) Return book                                           ." << std::endl;
    std::cout << ". 3) Look up book information                              ." << std::endl;
    std::cout << ". 4) Look up your personal borrow information              ." << std::endl;
    std::cout << "............................................................" << std::endl;
}

/* 用户借书 */
void user_borrow_book(bookshelf &BookShelf, userLists &UserLists, std::string &user_name) {
    std::cout << "Please input your ID as certification" << std::endl;

    std::string user_id, book_id, book_name;
    std::cin >> user_id;
    User* user_ptr = UserLists.get_user(user_id, user_name);
    if (user_ptr == nullptr) {
        std::cout << "Fail to get your information." << std::endl;
        return;
    }
    std::cout << "Please input the id and name of the book you want to borrow." << std::endl;
    std::cout << "For example: 12345 Book_and_Book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::cin >> book_id >> book_name;
    Book* book_ptr = BookShelf.get_book(book_id, book_name);
    if (book_ptr == nullptr) {
        std::cout << "Fail to get the book information" << std::endl;
    } else if(book_ptr->available_number == 0) {
        std::cout << "All the books are rented, try to borrow it next time." << std::endl;
    } else {
        book_ptr->available_number -= 1;
        (book_ptr->owner_info).add(std::make_pair(user_id, user_name));
        user_ptr->owned_book_number += 1;
        (user_ptr->owning_info).add(std::make_pair(book_id, book_name));

        std::cout << "Success!" << std::endl;
    }
}

/* 用户还书 */
void user_return_book(bookshelf &BookShelf, userLists &UserLists, std::string &user_name) {
    std::cout << "Please input your ID as certification" << std::endl;

    std::string user_id, book_id, book_name;
    std::cin >> user_id;
    User* user_ptr = UserLists.get_user(user_id, user_name);
    if (user_ptr == nullptr) {
        std::cout << "Fail to get your information." << std::endl;
        return;
    }

    std::cout << "Please input the id and name of the book you want to borrow." << std::endl;
    std::cout << "For example: 12345 Book_and_Book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::cin >> book_id >> book_name;
    Book* book_ptr = BookShelf.get_book(book_id, book_name);
    bool is_success_in_user = (user_ptr->owning_info).remove(std::make_pair(book_id, book_name));
    bool is_success_in_book = (book_ptr->owner_info).remove(std::make_pair(user_id, user_name));

    if (is_success_in_book && is_success_in_user) {
        book_ptr->available_number += 1;
        user_ptr->owned_book_number -= 1;
        std::cout << "Success" << std::endl;
    } else if (is_success_in_user) {
        user_ptr->owned_book_number -= 1;
        std::cout << "Something interesting happens." << std::endl;
    } else if (is_success_in_book) {
        book_ptr->available_number += 1;
        std::cout << "Something interesting happens." << std::endl;
    } else {
        std::cout << "Fail to return the book. Please check your input information." << std::endl;
    }
}

/* 用户查询书籍信息 */
void user_look_up_book_info(bookshelf &BookShelf) {
    std::cout << "Input the id and name of book you want to look up" << std::endl;
    std::cout << "For example: 12345 Book_and_Book" << std::endl;
    std::cout << "Attention: If there is space in the book_name, place it with _ " << std::endl;
    std::cout << std::endl;

    std::string id, name;
    std::cin >> id >> name;
    Book* book_ptr = BookShelf.get_book(id, name);
    if (book_ptr == nullptr) {
        std::cout << "The book doesn't exist, please check your input info" << std::endl;
    } else {
        std::cout << "Book ID:          " << book_ptr->book_id << std::endl;
        std::cout << "Book Name:        " << book_ptr->book_name << std::endl;
        std::cout << "Book Number:      " << book_ptr->book_number << std::endl;
        std::cout << "Available Number: " << book_ptr->available_number << std::endl;
    }
}

/* 用户查询自己的借阅信息 */
void user_look_up_borrow_info(userLists &UserLists, std::string &user_name) {
    std::cout << "Please input your id as certification" << std::endl;

    std::string id;
    std::cin >> id;
    User* user_ptr = UserLists.get_user(id, user_name);
    if (user_ptr == nullptr) {
        std::cout << "The information doesn't exist, please check your input info" << std::endl;
    } else {
        std::cout << "User ID:          " << user_ptr->user_id << std::endl;
        std::cout << "User Name:        " << user_ptr->user_name << std::endl;
        std::cout << "Borrow Number:    " << user_ptr->owned_book_number << std::endl;
        std::cout << "Borrow information: " << std::endl;

        int enumerate = 1;
        for (const auto &borrow_pair: user_ptr->owning_info) {
            std::cout << enumerate << ") " << borrow_pair.first << " " << borrow_pair.second << std::endl;
            enumerate += 1;
        }
    }
}
