// https://open.kattis.com/problems/spiderman

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int h[41];
pair<int, long> dp[41][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;

        for (int j = 0; j < m; ++j) {
            cin >> h[j];
        }

        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= 1000; ++k) {
                dp[j][k] = {1000, -1};
            }
        }

        dp[0][0] = {0, 0};

        for (int j = 0; j < m; ++j) {
            for (int k = 0; k <= 1000 - h[j]; ++k) {
                if (dp[j + 1][k + h[j]].first > max(dp[j][k].first, k + h[j])) {
                    dp[j + 1][k + h[j]] = {max(dp[j][k].first, k + h[j]), dp[j][k].second + (1l << j)};
                }

                if (dp[j + 1][k].first > dp[j][k + h[j]].first) {
                    dp[j + 1][k] = {dp[j][k + h[j]].first, dp[j][k + h[j]].second};
                }
            }
        }

        // for (int j = 0; j <= m; ++j) {
        //     for (int k = 0; k <= 20; ++k) {
        //         cerr << dp[j][k].first << ':' << dp[j][k].second << '\t';
        //     }
        //     cerr << endl;
        // }

        if (dp[m][0].second >= 0) {
            for (int j = 0; j < m; ++j) {
                cout << "DU"[(dp[m][0].second >> j) & 1];
            }

            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
