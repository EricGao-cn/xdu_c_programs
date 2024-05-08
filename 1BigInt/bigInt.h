#include<iostream>
#include<vector>
#include<string>

class bigInt{
    private:
        std::vector<int> num;
        bool negetive;

    public:
        bigInt();
        bigInt(const std::string &s);
        bigInt(const bigInt &other);

        bigInt operator+(const bigInt &other);
        bigInt operator-(const bigInt &other);
        bigInt convertToNeg(const bigInt &other);
        bool biggerAbs(const bigInt &other);  // 如果比other的绝对值更大，返回true

        friend std::ostream &operator<<(std::ostream &out, const bigInt &number);

};
