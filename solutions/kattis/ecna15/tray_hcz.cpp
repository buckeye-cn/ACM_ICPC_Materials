// https://open.kattis.com/problems/tray

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int used_mask[24];
long dp[26][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;

        used_mask[int(x)] |= 1 << int(y);
    }

    dp[0][0] = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j & used_mask[i]) continue;

            // ... ..| .|. .|| |.. |.| ||. |||
            // .-- |-- --. --|

            if (((j | used_mask[i]) & 0) == 0) dp[i + 1][0] += dp[i][j];
            if (((j | used_mask[i]) & 1) == 0) dp[i + 1][1] += dp[i][j];
            if (((j | used_mask[i]) & 2) == 0) dp[i + 1][2] += dp[i][j];
            if (((j | used_mask[i]) & 3) == 0) dp[i + 1][3] += dp[i][j];
            if (((j | used_mask[i]) & 4) == 0) dp[i + 1][4] += dp[i][j];
            if (((j | used_mask[i]) & 5) == 0) dp[i + 1][5] += dp[i][j];
            if (((j | used_mask[i]) & 6) == 0) dp[i + 1][6] += dp[i][j];
            if (((j | used_mask[i]) & 7) == 0) dp[i + 1][7] += dp[i][j];
            if (((j | used_mask[i]) & 3) == 0) dp[i + 1][0] += dp[i][j];
            if (((j | used_mask[i]) & 7) == 0) dp[i + 1][4] += dp[i][j];
            if (((j | used_mask[i]) & 6) == 0) dp[i + 1][0] += dp[i][j];
            if (((j | used_mask[i]) & 7) == 0) dp[i + 1][1] += dp[i][j];
        }
    }

    cout << dp[m][0] << endl;

    return 0;
}
