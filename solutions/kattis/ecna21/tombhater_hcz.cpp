// https://open.kattis.com/problems/tombhater

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char grid[50][50];
string word[50];

int dp[2][50][2500][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n, k;
    cin >> m >> n >> k;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int s = 0; s < k; ++s) {
        cin >> word[s];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int s = 0; s < k; ++s) {
                for (int t = 0; t < word[s].size(); ++t) {
                    if (word[s][t] == grid[i][j]) {
                        int prev = t ? 50 * s + t : 0;
                        int curr = t < word[s].size() - 1 ? 50 * s + t + 1 : 0;

                        if (i) {
                            int x = max(dp[~i & 1][j][prev][0], dp[~i & 1][j][prev][1]);

                            dp[i & 1][j][curr][0] = max(dp[i & 1][j][curr][0], x + 9999);
                            dp[i & 1][j][curr][1] = max(dp[i & 1][j][curr][1], x + 9999);
                        } else if (!t) {
                            dp[i & 1][j][curr][0] = 9999;
                            dp[i & 1][j][curr][1] = 9999;
                        }
                    }
                }
            }
        }

        for (int j = 1; j < n; ++j) {
            for (int s = 0; s < k; ++s) {
                for (int t = 0; t < word[s].size(); ++t) {
                    if (word[s][t] == grid[i][j]) {
                        int prev = t ? 50 * s + t : 0;
                        int curr = t < word[s].size() - 1 ? 50 * s + t + 1 : 0;

                        dp[i & 1][j][curr][0] = max(dp[i & 1][j][curr][0], dp[i & 1][j - 1][prev][0] - 1);
                    }
                }
            }
        }

        for (int j = n - 2; j >= 0; --j) {
            for (int s = 0; s < k; ++s) {
                for (int t = 0; t < word[s].size(); ++t) {
                    if (word[s][t] == grid[i][j]) {
                        int prev = t ? 50 * s + t : 0;
                        int curr = t < word[s].size() - 1 ? 50 * s + t + 1 : 0;

                        dp[i & 1][j][curr][1] = max(dp[i & 1][j][curr][1], dp[i & 1][j + 1][prev][1] - 1);
                    }
                }
            }
        }
    }

    int res = 0;

    for (int j = 0; j < n; ++j) {
        res = max(res, dp[~m & 1][j][0][0]);
        res = max(res, dp[~m & 1][j][0][1]);
    }

    if (res > 10000 * (m - 1)) {
        cout << 10000 * m - res << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
