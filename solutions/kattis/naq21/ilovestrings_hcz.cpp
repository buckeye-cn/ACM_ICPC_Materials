// https://open.kattis.com/problems/ilovestrings

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

int vmap[] {
    0, 1, 0, 0, 0, 2, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 0, 0, 0, 7, 0, 0,
    0, 8, 0, 0, 0, 0, 0, 9,
    0, 0, 0, 0, 0, 10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
int cmap[] {
    0, 0, 1, 2, 3, 0, 4, 5,
    6, 0, 7, 8, 9, 10, 11, 0,
    12, 13, 14, 15, 16, 0, 17, 18,
    19, 20, 21, 0, 0, 0, 0, 0,
    0, 0, 22, 23, 24, 0, 25, 26,
    27, 0, 28, 29, 30, 31, 32, 0,
    33, 34, 35, 36, 37, 0, 38, 39,
    40, 41, 42, 0, 0, 0, 0, 0,
};
int dp[11][43][11][43];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string word;
    cin >> word;

    long result = 0;

    for (int i = 0; i < word.size(); ++i) {
        if (vmap[word[i] - 64]) {
            int pos = vmap[word[i] - 64];

            dp[pos][0][0][0] += 1;

            if (dp[pos][0][0][0] >= MOD) {
                dp[pos][0][0][0] -= MOD;
            }

            for (int j = 1; j <= 10; ++j) {
                if (j == pos) continue;

                for (int k = 1; k <= 42; ++k) {
                    dp[min(j, pos)][k][max(j, pos)][0] += dp[j][k][0][0];

                    if (dp[min(j, pos)][k][max(j, pos)][0] >= MOD) {
                        dp[min(j, pos)][k][max(j, pos)][0] -= MOD;
                    }

                    for (int s = j + 1; s <= 10; ++s) {
                        if (s == pos) continue;

                        for (int t = k + 1; t <= 42; ++t) {
                            result += dp[j][k][s][t];
                        }
                    }
                }
            }
        } else {
            int pos = cmap[word[i] - 64];

            for (int j = 1; j <= 10; ++j) {
                dp[j][pos][0][0] += dp[j][0][0][0];

                if (dp[j][pos][0][0] >= MOD) {
                    dp[j][pos][0][0] -= MOD;
                }

                for (int k = 1; k <= 42; ++k) {
                    if (k == pos) continue;

                    for (int s = j + 1; s <= 10; ++s) {
                        dp[j][min(k, pos)][s][max(k, pos)] += dp[j][k][s][0];

                        if (dp[j][min(k, pos)][s][max(k, pos)] >= MOD) {
                            dp[j][min(k, pos)][s][max(k, pos)] -= MOD;
                        }
                    }
                }
            }
        }
    }

    cout << result % MOD << endl;

    return 0;
}
