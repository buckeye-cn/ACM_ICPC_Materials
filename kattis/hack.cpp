// https://open.kattis.com/problems/hack

#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

int trans[7][1000000] = {
    {},
    {},
    {
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
    }
};

int p10(int x) {
    int result = 1;

    for (int i = 0; i < x; ++i) {
        result *= 10;
    }

    return result;
}

void write_num(int x, int size) {
    for (int i = 0; i < size; ++i) {
        cout << char('0' + x / p10(size - i - 1) % 10);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
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
                case '0': cout << "9"  << endl << "1 2 3 4 5 6 7 8 9" << endl; break;
                case '1': cout << "10" << endl << "0 1 2 3 4 5 6 7 8 9" << endl; break;
                case '2': cout << "11" << endl << "1 0 1 2 3 4 5 6 7 8 9" << endl; break;
                case '3': cout << "12" << endl << "2 1 0 1 2 3 4 5 6 7 8 9" << endl; break;
                case '4': cout << "13" << endl << "3 2 1 0 1 2 3 4 5 6 7 8 9" << endl; break;
                case '5': cout << "13" << endl << "6 7 8 9 8 7 6 5 4 3 2 1 0" << endl; break;
                case '6': cout << "12" << endl << "7 8 9 8 7 6 5 4 3 2 1 0" << endl; break;
                case '7': cout << "11" << endl << "8 9 8 7 6 5 4 3 2 1 0" << endl; break;
                case '8': cout << "10" << endl << "9 8 7 6 5 4 3 2 1 0" << endl; break;
                case '9': cout << "9"  << endl << "8 7 6 5 4 3 2 1 0" << endl; break;
            }
        } else {
            int tot = p10(s.size()) - 1;
            int pos = stoi(s, 0, 10);

            pos = trans[s.size()][pos];
            cout << tot << endl;
            write_num(pos, s.size());

            for (int i = 1; i < tot; ++i) {
                pos = trans[s.size()][pos];
                cout << ' ';
                write_num(pos, s.size());
            }

            cout << endl;
        }
    }
}
