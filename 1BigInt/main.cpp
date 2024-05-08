#include "bigInt.h"
#include <utility>

void calc(std::string &a, std::string &b) {
    bigInt num1(a);
    bigInt num2(b);

    bigInt sum = num1 + num2;
    std::cout << num1 << " + " << num2 << " = " << sum << std::endl;
    bigInt sub = num1 - num2;
    std::cout << num1 << " - " << num2 << " = " << sub << std::endl;
    std::cout << std::endl;
}

int main(){
    std::vector<std::pair<std::string, std::string> > num_pairs{
        std::make_pair("3", "2"), std::make_pair("2", "3"),
        std::make_pair("1234567890", "987654321"), std::make_pair("-9999999999999999", "1"),
        std::make_pair("-246810", "-13579"), std::make_pair("114514", "-1919810"),
        std::make_pair("0", "0")};

    for(auto num_pair : num_pairs) {
        calc(num_pair.first, num_pair.second);
    }

    std::string a, b;
    std::cout << "Please input two big integers: " << std::endl;
    std::cin >> a >> b;
    calc(a, b);

    return 0;
}