// https://open.kattis.com/problems/justpassingthrough

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int grid[600][600];
int dp[600][600][11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int r, c, n;
    cin >> r >> c >> n;

    for (int i = 0; i <= r + 1; ++i) {
        for (int j = 0; j <= c + 1; ++j) {
            grid[i][j] = -1;

            for (int k = 0; k <= n; ++k) {
                dp[i][j][k] = 1e6;
            }
        }

        dp[i][0][0] = 0;
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int j = 1; j <= c; ++j) {
        for (int i = 1; i <= r; ++i) {
            if (grid[i][j] < 0) continue;

            bool pass = grid[i][j - 1] >= 0
                && grid[i][j + 1] >= 0
                && grid[i][j - 1] < grid[i][j]
                && grid[i][j + 1] < grid[i][j]
                && grid[i - 1][j] > grid[i][j]
                && grid[i + 1][j] > grid[i][j];

            for (int k = pass; k <= n; ++k) {
                dp[i][j][k] = min(
                    min(
                        dp[i - 1][j - 1][k - pass],
                        dp[i][j - 1][k - pass]
                    ),
                    dp[i + 1][j - 1][k - pass]
                ) + grid[i][j];
            }
        }
    }

    // for (int i = 1; i <= r; ++i) {
    //     for (int j = 1; j <= c; ++j) {
    //         for (int k = 0; k <= n; ++k) {
    //             if (dp[i][j][k] < 1e6) {
    //                 cerr << dp[i][j][k] << ',';
    //             } else {
    //                 cerr << 'x' << ',';
    //             }
    //         }
    //         cerr << '\t';
    //     }
    //     cerr << endl;
    // }

    int best = 1e6;

    for (int i = 1; i <= r; ++i) {
        best = min(best, dp[i][c][n]);
    }

    if (best < 1e6) {
        cout << best << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
