//
// Created by 高宇轩 on 24-4-20.
//

#ifndef INC_5LIBRARY_USERLIST_H
#define INC_5LIBRARY_USERLIST_H
#include <string>
#include <utility>
#include "LinkedList.h"

typedef struct user {
    std::string user_id;
    std::string user_name;
    int owned_book_number;
    LinkedList<std::pair<std::string, std::string> > owning_info;

    user(std::string &id, std::string &name, int owning_num):
        user_id(id), user_name(name), owned_book_number(owning_num) {};
} User;

class UserLinkedList : public LinkedList<User*> {
public:
    /* 重写remove方法，便于直接删去id和name对应的用户 */
    bool remove(std::string &id, std::string &name);

    /* 重写get方法，便于直接得到id和name对应用户的指针 */
    User* get(std::string &id, std::string &name);
};


class userLists {
private:
    int number_of_users{0};

public:

    UserLinkedList lst;
    /* 新增用户信息 */
    void add_user(std::string &id, std::string &name, int owning_num);

    /* 删除用户信息，删除成功返回true */
    bool delete_user(std::string &id, std::string &name);

    /* 返回id和name对应的用户，如果没找到返回nullptr */
    User* get_user(std::string &id, std::string &name);

    /* 获取用户的数量 */
    int get_user_number() const;


};
#endif //INC_5LIBRARY_USERLIST_H
