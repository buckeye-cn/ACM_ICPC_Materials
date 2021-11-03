// https://open.kattis.com/problems/kinkywordsearch

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char grid[16][16];
bool dp[100][16][16][100][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int r, c;
    cin >> r >> c;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> grid[i][j];
        }
    }

    int kk;
    string word;
    cin >> kk >> word;

    if (kk >= 100) {
        cout << "No" << endl;

        return 0;
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (grid[i][j] == word[0]) {
                for (int s = 0; s < 8; ++s) {
                    dp[0][i][j][0][s] = true;
                }
            }
        }
    }

    for (int d = 1; d < word.size(); ++d) {
        for (int i = 1; i <= r; ++i) {
            for (int j = 1; j <= c; ++j) {
                if (grid[i][j] == word[d]) {
                    dp[d][i][j][0][0] = dp[d - 1][i - 1][j - 1][0][0];
                    dp[d][i][j][0][1] = dp[d - 1][i - 1][j    ][0][1];
                    dp[d][i][j][0][2] = dp[d - 1][i - 1][j + 1][0][2];
                    dp[d][i][j][0][3] = dp[d - 1][i    ][j - 1][0][3];
                    dp[d][i][j][0][4] = dp[d - 1][i    ][j + 1][0][4];
                    dp[d][i][j][0][5] = dp[d - 1][i + 1][j - 1][0][5];
                    dp[d][i][j][0][6] = dp[d - 1][i + 1][j    ][0][6];
                    dp[d][i][j][0][7] = dp[d - 1][i + 1][j + 1][0][7];

                    for (int k = 1; k <= kk; ++k) {
                        for (int s = 0; s < 8; ++s) {
                            dp[d][i][j][k][0] |= dp[d - 1][i - 1][j - 1][k - (d > 1 && s != 0)][s];
                            dp[d][i][j][k][1] |= dp[d - 1][i - 1][j    ][k - (d > 1 && s != 1)][s];
                            dp[d][i][j][k][2] |= dp[d - 1][i - 1][j + 1][k - (d > 1 && s != 2)][s];
                            dp[d][i][j][k][3] |= dp[d - 1][i    ][j - 1][k - (d > 1 && s != 3)][s];
                            dp[d][i][j][k][4] |= dp[d - 1][i    ][j + 1][k - (d > 1 && s != 4)][s];
                            dp[d][i][j][k][5] |= dp[d - 1][i + 1][j - 1][k - (d > 1 && s != 5)][s];
                            dp[d][i][j][k][6] |= dp[d - 1][i + 1][j    ][k - (d > 1 && s != 6)][s];
                            dp[d][i][j][k][7] |= dp[d - 1][i + 1][j + 1][k - (d > 1 && s != 7)][s];
                        }
                    }
                }
            }
        }
    }

    // for (int d = 0; d < word.size(); ++d) {
    //     for (int i = 1; i <= r; ++i) {
    //         for (int j = 1; j <= c; ++j) {
    //             for (int k = 0; k <= kk; ++k) {
    //                 for (int s = 0; s < 8; ++s) {
    //                     if (dp[d][i][j][k][s]) {
    //                         cerr << d << i << j << k << s << endl;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            for (int s = 0; s < 8; ++s) {
                if (dp[word.size() - 1][i][j][kk][s]) {
                    cout << "Yes" << endl;

                    return 0;
                }
            }
        }
    }

    cout << "No" << endl;

    return 0;
}
