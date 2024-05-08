//
// Created by 高宇轩 on 24-4-20.
//

#include "utils.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -a(-u) username" << std::endl;
        return 1;
    }

    bookshelf BookShelf;
    userLists UserLists;

    // 解析命令行参数
    std::string identity = argv[1];
    std::string username = argv[2];

    // 根据用户身份调用相应的函数
    if (identity == "-a") {
        // 调用管理员操作函数
        admin_action(BookShelf, UserLists);
    } else if (identity == "-u") {
        // 调用读者操作函数
        user_action(BookShelf, UserLists, username);
    } else if (identity == "-h") {
        std::cout << "Libsim [-a/-u] [username]" << std::endl;
        std::cout << "-a  If your are the administrator" << std::endl;
        std::cout << "-u  If your are the user" << std::endl;
        std::cout << "When you input your username, please place the space with underline '_'" << std::endl;
    } else {
            std::cerr << "Invalid user identity: " << identity << std::endl;
            return 1;
        }

    return 0;
}