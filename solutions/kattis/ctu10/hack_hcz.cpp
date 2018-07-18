// https://open.kattis.com/problems/hack

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int trans2[100] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  19,
    0,  21, 11, 12, 13, 14, 15, 16, 17, 18,
    10, 22, 23, 24, 25, 26, 27, 28, 29, 39,
    20, 41, 31, 32, 33, 34, 35, 36, 37, 38,
    30, 42, 43, 44, 45, 46, 47, 48, 49, 59,
    40, 61, 51, 52, 53, 54, 55, 56, 57, 58,
    50, 62, 63, 64, 65, 66, 67, 68, 69, 79,
    60, 81, 71, 72, 73, 74, 75, 76, 77, 78,
    70, 82, 83, 84, 85, 86, 87, 88, 89, 99,
    80, 90, 91, 92, 93, 94, 95, 96, 97, 98,
};
int trans3[1000];
int trans4[10000];
int trans5[100000];
int trans6[1000000];

int *trans[7] = {nullptr, nullptr, trans2, trans3, trans4, trans5, trans6};

int p10(int x) {
    int result = 1;

    for (int i = 0; i < x; ++i) {
        result *= 10;
    }

    return result;
}

void write_num(int x, int size) {
    for (int i = 0; i < size; ++i) {
        putchar('0' + x / p10(size - i - 1) % 10);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 3; i <= 6; ++i) {
        int tot = p10(i - 1);
        int pos = 0;
        bool odd = false;

        for (int j = 0; j < tot; ++j) {
            if (odd) {
                trans[i][pos * 10] = trans[i - 1][pos] * 10;

                for (int k = 1; k <= 9; ++k) {
                    trans[i][pos * 10 + k] = pos * 10 + k - 1;
                }
            } else {
                for (int k = 0; k <= 8; ++k) {
                    trans[i][pos * 10 + k] = pos * 10 + k + 1;
                }

                trans[i][pos * 10 + 9] = trans[i - 1][pos] * 10 + 9;
            }

            pos = trans[i - 1][pos];
            odd = !odd;
        }
    }

    while (true) {
        string s;

        cin >> s;

        if (s == "-1") {
            return 0;
        }

        if (s.size() == 1) {
            switch (s[0]) {
                case '0': printf("9\n1 2 3 4 5 6 7 8 9\n"); break;
                case '1': printf("10\n0 1 2 3 4 5 6 7 8 9\n"); break;
                case '2': printf("11\n1 0 1 2 3 4 5 6 7 8 9\n"); break;
                case '3': printf("12\n2 1 0 1 2 3 4 5 6 7 8 9\n"); break;
                case '4': printf("13\n3 2 1 0 1 2 3 4 5 6 7 8 9\n"); break;
                case '5': printf("13\n6 7 8 9 8 7 6 5 4 3 2 1 0\n"); break;
                case '6': printf("12\n7 8 9 8 7 6 5 4 3 2 1 0\n"); break;
                case '7': printf("11\n8 9 8 7 6 5 4 3 2 1 0\n"); break;
                case '8': printf("10\n9 8 7 6 5 4 3 2 1 0\n"); break;
                case '9': printf("9\n8 7 6 5 4 3 2 1 0\n"); break;
            }
        } else {
            int tot = p10(s.size()) - 1;
            int pos = stoi(s, 0, 10);

            pos = trans[s.size()][pos];
            printf("%d\n", tot);
            write_num(pos, s.size());

            for (int i = 1; i < tot; ++i) {
                pos = trans[s.size()][pos];
                putchar(' ');
                write_num(pos, s.size());
            }

            putchar('\n');
        }
    }
}
