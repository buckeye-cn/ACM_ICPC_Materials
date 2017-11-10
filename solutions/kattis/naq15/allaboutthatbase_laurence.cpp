#include <iostream>
#include <string>
#include <utility>

using namespace std;

const char RADIX[] = {'!', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0'};

inline long parse_digit(char c, int base) {
    if (base == 1) {
        if (c == '1')
            return 1;
    } else if (base <= 10) {
        if ('0' <= c && c <= (base-1 + '0'))
            return c - '0';
    } else {
        if ('0' <= c && c <= '9')
            return c - '0';
        else if  ('a' <= c && c <= (base-11 + 'a'))
            return c - 'a' + 10;
    }
    return -1;
}

inline long parse_int(string& s, int base) {
    long n = 0;

    for (char c : s) {
        long d = parse_digit(c, base);
        if (d < 0) {
            return d;
        }
        n *= base;
        n += d;
    }

    return n;
}

int main() {
    int N;
    cin >> N;

    for (int _i = 0; _i < N; _i++) {
        string n1, n2, n3;
        char op, _;
        cin >> n1 >> op >> n2 >> _ >> n3;
        if (op == '-') {
            swap(n1, n3);
            op = '+';
        } else if (op == '/') {
            swap(n1, n3);
            op = '*';
        }

        bool valid = false;
        for (int i = 1; i <= 36; i++) {
            long num1 = parse_int(n1, i);
            long num2 = parse_int(n2, i);
            long num3 = parse_int(n3, i);
            if (num1 > 0 && num2 > 0 && num3 > 0 && ((op == '+' && num1 + num2 == num3) || (op == '*' && num1 * num2 == num3))) {
                cout << RADIX[i];
                valid = true;
            }
        }
        if (!valid) {
            cout << "invalid";
        }
        cout << "\n";
    }
}
