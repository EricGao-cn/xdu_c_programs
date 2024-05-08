#include "bigInt.h"

bigInt::bigInt() {
    negetive = false;
    num = {0};
}

/* 将输入的string转化为bigInt类 */
bigInt::bigInt(const std::string &s) {
    negetive = false;
    if (s[0] == '-') {
        negetive = true;
    }
    for (int i = s.length() - 1; i >= (negetive ? 1 : 0); i--) {
        num.push_back(s[i] - '0');
    }
}

bigInt::bigInt(const bigInt &other) {
    negetive = other.negetive;
    for (int i = 0; i < other.num.size(); i++) {
        num.push_back(other.num[i]);
    }
}

/* 辅助函数，把bigInt转化为一个绝对值相同，但是符号相反的新bigInt */
bigInt bigInt::convertToNeg(const bigInt &other) {
    bigInt neg = bigInt(other);
    neg.negetive = !neg.negetive;
    return neg;
}

/* 如果比括号中的bigInt绝对值更大，返回true */
bool bigInt::biggerAbs(const bigInt &other) {
    if (num.size() < other.num.size()) {
        return false;
    } else if (num.size() > other.num.size()) {
        return true;
    } else {
        int i = num.size() - 1;
        while (i >= 0) {
            if (num[i] != other.num[i]) {
                return num[i] > other.num[i];
            } else {
                i--;
            }
        }
        return true;   // 如果相等也返回true
    }
}

/* 重载 + 运算符，模拟两个整数的竖式加法 */
bigInt bigInt::operator+(const bigInt &other) {
    if (negetive && !other.negetive) {
        return *this - convertToNeg(other);
    } else if (!negetive && other.negetive) {
        return *this - convertToNeg(other);
    }

    bigInt ans;
    ans.num.clear();
    if (negetive && other.negetive) {
        ans.negetive = true;
    }
    bool up = false;
    int i = 0;

    for (; i < std::min(num.size(), other.num.size()); i++) {
        ans.num.push_back((num[i] + other.num[i] + up) % 10);
        up = ((num[i] + other.num[i] + up) >= 10);
    }

    while (i < num.size()) {
        ans.num.push_back((num[i] + up) % 10);
        up = ((num[i] + up) >= 10);
        i++;
    }

    while (i < other.num.size()) {
        ans.num.push_back((other.num[i] + up) % 10);
        up = ((other.num[i] + up) >= 10);
        i++;
    }
    if (up) {
        ans.num.push_back(up);
    }

    return ans;
}

/* 重载 - 运算符，先判断结果的正负，然后用大的绝对值减小的绝对值 */
bigInt bigInt::operator-(const bigInt &other) {
    if (!negetive && other.negetive) {
        return (*this) + convertToNeg(other);
    } else if (negetive && !other.negetive){
        return convertToNeg(convertToNeg(*this) + other);
    }

    bigInt ans;
    ans.num.clear();
    if ((!negetive && !other.negetive && !biggerAbs(other)) || (negetive && other.negetive && biggerAbs(other))) {
        ans.negetive = true;
    } else {
        ans.negetive = false;
    }

    bigInt bigger = bigInt(biggerAbs(other) ? *this : other);
    bigInt smaller = bigInt(biggerAbs(other) ? other : *this);
    bool down = false;
    int i = 0, tmp;
    while (i < smaller.num.size()) {
        tmp = bigger.num[i] - smaller.num[i] - down;
        down = (tmp < 0);
        tmp = tmp + 10 * down;
        ans.num.push_back(tmp);
        i++;
    }

    while (i < bigger.num.size()) {
        tmp = bigger.num[i] - down;
        down = (tmp < 0);
        tmp = tmp + 10 * down;
        ans.num.push_back(tmp);
        i++;
    }

    return ans;
}

/* 重载 << ，使得bigInt类能够直接输出 */
std::ostream &operator<<(std::ostream &out, const bigInt &number) {
    std::string ans;
    bool frontZero = true;
    for (int i = number.num.size() - 1; i >= 0; i--) {
        if (frontZero && number.num[i] == 0) {
            continue;
        } else {
            ans += std::to_string(number.num[i]);
            frontZero = false;
        }
    }
    if (ans.empty()) {
        ans = "0";
    }
    if (number.negetive && ans != "0") {
        out << "-";
    }
    out << ans;
    return out;
}
