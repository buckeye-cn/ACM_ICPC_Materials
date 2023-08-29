// https://open.kattis.com/problems/amusicalquestion

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

uint64_t dp[2001][32];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    dp[1000][16] = 1;

    int c, n;
    cin >> c >> n;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;

        if (v > c) continue;

        if (v & 63) {
            for (int j = c + 1000; j >= 1000; --j) {
                dp[j][31] |= dp[j - v][31] | (dp[j][31 - (v >> 6)] << (v & 63)) | (dp[j][30 - (v >> 6)] >> (-v & 63));
                dp[j][30] |= dp[j - v][30] | (dp[j][30 - (v >> 6)] << (v & 63)) | (dp[j][29 - (v >> 6)] >> (-v & 63));
                dp[j][29] |= dp[j - v][29] | (dp[j][29 - (v >> 6)] << (v & 63)) | (dp[j][28 - (v >> 6)] >> (-v & 63));
                dp[j][28] |= dp[j - v][28] | (dp[j][28 - (v >> 6)] << (v & 63)) | (dp[j][27 - (v >> 6)] >> (-v & 63));
                dp[j][27] |= dp[j - v][27] | (dp[j][27 - (v >> 6)] << (v & 63)) | (dp[j][26 - (v >> 6)] >> (-v & 63));
                dp[j][26] |= dp[j - v][26] | (dp[j][26 - (v >> 6)] << (v & 63)) | (dp[j][25 - (v >> 6)] >> (-v & 63));
                dp[j][25] |= dp[j - v][25] | (dp[j][25 - (v >> 6)] << (v & 63)) | (dp[j][24 - (v >> 6)] >> (-v & 63));
                dp[j][24] |= dp[j - v][24] | (dp[j][24 - (v >> 6)] << (v & 63)) | (dp[j][23 - (v >> 6)] >> (-v & 63));
                dp[j][23] |= dp[j - v][23] | (dp[j][23 - (v >> 6)] << (v & 63)) | (dp[j][22 - (v >> 6)] >> (-v & 63));
                dp[j][22] |= dp[j - v][22] | (dp[j][22 - (v >> 6)] << (v & 63)) | (dp[j][21 - (v >> 6)] >> (-v & 63));
                dp[j][21] |= dp[j - v][21] | (dp[j][21 - (v >> 6)] << (v & 63)) | (dp[j][20 - (v >> 6)] >> (-v & 63));
                dp[j][20] |= dp[j - v][20] | (dp[j][20 - (v >> 6)] << (v & 63)) | (dp[j][19 - (v >> 6)] >> (-v & 63));
                dp[j][19] |= dp[j - v][19] | (dp[j][19 - (v >> 6)] << (v & 63)) | (dp[j][18 - (v >> 6)] >> (-v & 63));
                dp[j][18] |= dp[j - v][18] | (dp[j][18 - (v >> 6)] << (v & 63)) | (dp[j][17 - (v >> 6)] >> (-v & 63));
                dp[j][17] |= dp[j - v][17] | (dp[j][17 - (v >> 6)] << (v & 63)) | (dp[j][16 - (v >> 6)] >> (-v & 63));
                dp[j][16] |= dp[j - v][16] | (dp[j][16 - (v >> 6)] << (v & 63));
            }
        } else {
            for (int j = c + 1000; j >= 1000; --j) {
                dp[j][31] |= dp[j - v][31] | dp[j][31 - (v >> 6)];
                dp[j][30] |= dp[j - v][30] | dp[j][30 - (v >> 6)];
                dp[j][29] |= dp[j - v][29] | dp[j][29 - (v >> 6)];
                dp[j][28] |= dp[j - v][28] | dp[j][28 - (v >> 6)];
                dp[j][27] |= dp[j - v][27] | dp[j][27 - (v >> 6)];
                dp[j][26] |= dp[j - v][26] | dp[j][26 - (v >> 6)];
                dp[j][25] |= dp[j - v][25] | dp[j][25 - (v >> 6)];
                dp[j][24] |= dp[j - v][24] | dp[j][24 - (v >> 6)];
                dp[j][23] |= dp[j - v][23] | dp[j][23 - (v >> 6)];
                dp[j][22] |= dp[j - v][22] | dp[j][22 - (v >> 6)];
                dp[j][21] |= dp[j - v][21] | dp[j][21 - (v >> 6)];
                dp[j][20] |= dp[j - v][20] | dp[j][20 - (v >> 6)];
                dp[j][19] |= dp[j - v][19] | dp[j][19 - (v >> 6)];
                dp[j][18] |= dp[j - v][18] | dp[j][18 - (v >> 6)];
                dp[j][17] |= dp[j - v][17] | dp[j][17 - (v >> 6)];
            }
        }
    }

    // for (int i = 0; i <= 100; ++i) {
    //     for (int j = 0; j <= 100; ++j) {
    //         if (dp[1000 + i][16 + (j >> 6)] & (1ul << (j & 63))) {
    //             cerr << 1;
    //         } else {
    //             cerr << 0;
    //         }
    //     }
    //     cerr << endl;
    // }

    for (int i = 2 * c; i >= 0; --i) {
        for (int j = (i + 1) / 2; j <= c && j <= i; ++j) {
            if (dp[1000 + i - j][16 + (j >> 6)] & (1ul << (j & 63))) {
                cout << j << ' ' << i - j << endl;
                return 0;
            }
        }
    }

    return 0;
}
