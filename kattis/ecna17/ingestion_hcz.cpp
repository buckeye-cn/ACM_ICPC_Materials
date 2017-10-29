// https://open.kattis.com/problems/ingestion

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n;
int init;
int lim[200];
int dp[200][200][3];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> init;

    for (int i = 0; i < n; ++i) {
        cin >> lim[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j][0] = -(1 << 30);
            dp[i][j][1] = -(1 << 30);
            dp[i][j][2] = -(1 << 30);
        }
    }
    dp[0][0][2] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            int w1 = init;
            for (int t = 0; t < j; ++t) {
                w1 = int(w1 * 2. / 3);
            }
            w1 = min(w1, lim[i]);

            if (dp[i + 1][j + 1][0] < dp[i][j][0] + w1) {
                dp[i + 1][j + 1][0] = dp[i][j][0] + w1;
            }
            if (dp[i + 1][j][1] < dp[i][j][0]) {
                dp[i + 1][j][1] = dp[i][j][0];
            }

            int w2 = init;
            for (int t = 0; t < j - 1; ++t) {
                w2 = int(w2 * 2. / 3);
            }
            w2 = min(w2, lim[i]);

            if (dp[i + 1][j][0] < dp[i][j][1] + w2) {
                dp[i + 1][j][0] = dp[i][j][1] + w2;
            }
            if (dp[i + 1][j][2] < dp[i][j][1]) {
                dp[i + 1][j][2] = dp[i][j][1];
            }

            int w3 = init;
            w3 = min(w3, lim[i]);

            if (dp[i + 1][1][0] < dp[i][j][2] + w3) {
                dp[i + 1][1][0] = dp[i][j][2] + w3;
            }
            if (dp[i + 1][j][2] < dp[i][j][2]) {
                dp[i + 1][j][2] = dp[i][j][2];
            }
        }
    }

    int best = 0;
    for (int j = 0; j <= n; ++j) {
        if (best < dp[n][j][0]) {
            best = dp[n][j][0];
        }
        if (best < dp[n][j][1]) {
            best = dp[n][j][1];
        }
        if (best < dp[n][j][2]) {
            best = dp[n][j][2];
        }
    }

    cout << best << endl;

    return 0;
}
