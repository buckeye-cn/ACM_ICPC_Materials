// https://open.kattis.com/problems/allaboutthatbase

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int ctoi(char c) {
    if (c <= '9') {
        return c - '0';
    } else {
        return c - 'a' + 10;
    }
}

char itoc(int i) {
    if (i <= 9) {
        return i + '0';
    } else if (i <= 35) {
        return i + 'a' - 10;
    } else {
        return '0';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s[3];
        char op, eq;
        cin >> s[0] >> op >> s[1] >> eq >> s[2];

        string result;

        for (int j = 1; j <= 36; ++j) {
            bool err = false;

            long a[3] {0, 0, 0};
            for (int k = 0; k < 3; ++k) {
                for (char c: s[k]) {
                    int digit = ctoi(c);

                    if (j > 1) {
                        err = err || digit >= j;
                    } else {
                        err = err || digit != 1;
                    }

                    a[k] = a[k] * j + digit;
                }

                err = err || a[k] >= 1l << 32;
            }

            switch (op) {
                case '+':
                    err = err || a[0] + a[1] != a[2];
                    break;
                case '-':
                    err = err || a[2] + a[1] != a[0];
                    break;
                case '*':
                    err = err || a[0] * a[1] != a[2];
                    break;
                case '/':
                    err = err || a[2] * a[1] != a[0];
                    break;
            }

            if (!err) {
                result += itoc(j);
            }
        }

        if (!result.empty()) {
            cout << result << endl;
        } else {
            cout << "invalid" << endl;
        }
    }

    return 0;
}
