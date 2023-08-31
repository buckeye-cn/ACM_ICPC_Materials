// https://open.kattis.com/problems/magicwordsquare

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char s[500][3];
int mask[500];
int exist[26][26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int m = 0;

    for (int i = 0; i < n; ++i) {
        cin >> s[m];
        s[m][0] -= 'a';
        s[m][1] -= 'a';
        s[m][2] -= 'a';

        if (s[m][0] != s[m][1] && s[m][0] != s[m][2] & s[m][1] != s[m][2]) {
            mask[m] = (1 << s[m][0]) | (1 << s[m][1]) | (1 << s[m][2]);
            exist[s[m][0]][s[m][1]] |= 1 << s[m][2];
            m += 1;
        }
    }

    int result = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mask[i] & mask[j]) continue;
            int m0 = ~mask[i] & ~mask[j] & exist[s[i][0]][s[j][0]] & exist[s[i][2]][s[j][1]];
            if (!m0) continue;
            int m1 = ~mask[i] & ~mask[j] & exist[s[i][1]][s[j][1]];
            if (!m1) continue;
            int m2 = ~mask[i] & ~mask[j] & exist[s[i][2]][s[j][2]] & exist[s[i][0]][s[j][1]];
            if (!m2) continue;

            for (int k = 0; k < m; ++k) {
                result += !(mask[i] & mask[k])
                    && !(mask[j] & mask[k])
                    && (m0 & (1 << s[k][0]))
                    && (m1 & (1 << s[k][1]))
                    && (m2 & (1 << s[k][2]));
            }
        }
    }

    cout << result << endl;

    return 0;
}
