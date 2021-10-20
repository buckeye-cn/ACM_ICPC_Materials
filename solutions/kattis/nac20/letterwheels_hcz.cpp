// https://open.kattis.com/problems/letterwheels

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int m;
int r[5000][3];
int h1;
int h2[5000];
int h3[5000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    m = s1.size();

    for (int i = 0; i < m; ++i) {
        r[i][0] = rand();
        r[i][1] = rand();
        r[i][2] = r[i][0] ^ r[i][1];
        s1[i] -= 'A';
        s2[i] -= 'A';
        s3[i] -= 'A';
    }

    s2 += s2;
    s3 += s3;

    for (int i = 0; i < m; ++i) {
        h1 ^= r[i][s1[i]];

        for (int j = 0; j < m; ++j) {
            h2[i] ^= r[j][s2[i + j]];
            h3[i] ^= r[j][s3[i + j]];
        }
    }

    int best = 1e6;

    for (int i = 0; i < m && best; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((h1 ^ h2[i] ^ h3[j]) == 0) {
                int d1 = min(i, m - i);
                int d2 = min(j, m - j);
                int d3 = min(abs(i - j), m - abs(i - j));

                best = min(best, d1 + d2);
                best = min(best, d2 + d3);
                best = min(best, d1 + d3);
            }
        }
    }

    if (best == 1e6) {
        cout << -1 << endl;
    } else {
        cout << best << endl;
    }

    return 0;
}
