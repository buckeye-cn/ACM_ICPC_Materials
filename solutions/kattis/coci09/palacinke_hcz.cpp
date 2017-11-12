// https://open.kattis.com/problems/palacinke

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 5557

using namespace std;

int n, m, t;
int item[30][30];
int dp_mat[2][60][60];
int dp[2][60];
int result[16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        string s;
        cin >> a >> b >> s;

        int bitmap = 0;
        for (char c: s) {
            switch (c) {
                case 'B':
                    bitmap |= 1;
                    break;
                case 'J':
                    bitmap |= 2;
                    break;
                case 'M':
                    bitmap |= 4;
                    break;
                case 'P':
                    bitmap |= 8;
                    break;
            }
        }

        item[a - 1][b - 1] = bitmap;
    }

    cin >> t;
    t += 1;

    for (int mask = 0; mask < 16; ++mask) {
        for (int i = 0; i < 2 * n + 1; ++i) {
            for (int j = 0; j < 2 * n + 1; ++j) {
                dp_mat[0][i][j] = 0;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp_mat[0][i][j] = int(item[i][j] != 0);
                dp_mat[0][i][j + n] = int(i == j);
                dp_mat[0][i + n][j] = int(item[i][j] != 0 && (item[i][j] & mask) == item[i][j]);
                dp_mat[0][i + n][j + n] = 0;
            }
        }
        dp_mat[0][0][2 * n] = 1;
        dp_mat[0][2 * n][2 * n] = 1;

        if (t & 1) {
            for (int i = 0; i < 2 * n + 1; ++i) {
                dp[0][i] = dp_mat[0][0][i];
            }
        } else {
            for (int i = 0; i < 2 * n + 1; ++i) {
                dp[0][i] = 0;
            }
            dp[0][0] = 1;
        }

        for (int depth = 1; t >= (1l << depth); ++depth) {
            memset(dp_mat[depth & 1], 0, sizeof(dp_mat[depth & 1]));
            memset(dp[depth & 1], 0, sizeof(dp[depth & 1]));

            for (int i = 0; i < 2 * n + 1; ++i) {
                for (int j = 0; j < 2 * n + 1; ++j) {
                    for (int k = 0; k < 2 * n + 1; ++k) {
                        dp_mat[depth & 1][i][k] += dp_mat[(depth & 1) ^ 1][i][j] * dp_mat[(depth & 1) ^ 1][j][k];
                    }
                }
            }

            for (int i = 0; i < 2 * n + 1; ++i) {
                for (int j = 0; j < 2 * n + 1; ++j) {
                    dp_mat[depth & 1][i][j] %= MOD;
                }
            }

            if (t & (1l << depth)) {
                for (int i = 0; i < 2 * n + 1; ++i) {
                    for (int j = 0; j < 2 * n + 1; ++j) {
                        dp[depth & 1][j] += dp_mat[depth & 1][i][j] * dp[(depth & 1) ^ 1][i];
                    }
                }

                for (int i = 0; i < 2 * n + 1; ++i) {
                    dp[depth & 1][i] %= MOD;
                }
            } else {
                for (int i = 0; i < 2 * n + 1; ++i) {
                    dp[depth & 1][i] = dp[(depth & 1) ^ 1][i];
                }
            }

            result[mask] = dp[depth & 1][2 * n];
        }

        // cout << mask << ' ' << result[mask] << endl;
    }

    int tot = result[15] - result[14] - result[13] + result[12]
            - result[11] + result[10] + result[9] - result[8]
            - result[7] + result[6] + result[5] - result[4]
            + result[3] - result[2] - result[1] + result[0];
    tot %= MOD;
    tot += MOD;
    tot %= MOD;

    cout << tot << endl;

    return 0;
}
