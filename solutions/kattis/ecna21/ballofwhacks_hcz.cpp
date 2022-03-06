// https://open.kattis.com/problems/ballofwhacks

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

char t1[] {
    -1,
    2, 3, 4, 5, 1, 7, 8, 9, 10, 6,
    13, 14, 15, 16, 17, 18, 19, 20, 11, 12,
    22, 23, 24, 25, 21, 27, 28, 29, 30, 26
};

char t2[] {
    -1,
    6, 11, 12, 7, 2, 20, 21, 13, 3, 1,
    25, 26, 27, 22, 14, 8, 4, 5, 10, 19,
    30, 28, 15, 9, 18, 24, 29, 23, 16, 17
};

char base[] {
    -1,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unordered_set<string> s {string(base)};

    for (int i = 0; i < 30; ++i) {
        for (string str: s) {
            for (int j = 1; j <= 30; ++j) {
                str[j] = t1[int(str[j])];
            }

            if (s.find(str) == s.end()) {
                s.insert(str);
                break;
            }
        }

        for (string str: s) {
            for (int j = 1; j <= 30; ++j) {
                str[j] = t2[int(str[j])];
            }

            if (s.find(str) == s.end()) {
                s.insert(str);
                break;
            }
        }
    }

    string str[3];

    for (int i = 0; i < 3; ++i) {
        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            int v;
            cin >> v;

            str[i].push_back(v);
        }
    }

    if (str[0].size() + str[1].size() + str[2].size() == 30) {
        int mask0 = 0;

        for (int i = 0; i < str[0].size(); ++i) {
            mask0 |= 1 << str[0][i];
        }

        for (string str1: s) {
            int mask1 = mask0;

            for (int i = 0; i < str[1].size(); ++i) {
                mask1 |= 1 << str1[str[1][i]];
            }

            for (string str2: s) {
                int mask2 = mask1;

                for (int i = 0; i < str[2].size(); ++i) {
                    mask2 |= 1 << str2[str[2][i]];
                }

                if (mask2 == 0x7ffffffe) {
                    cout << "Yes" << endl;

                    return 0;
                }
            }
        }
    }

    cout << "No" << endl;

    return 0;
}
