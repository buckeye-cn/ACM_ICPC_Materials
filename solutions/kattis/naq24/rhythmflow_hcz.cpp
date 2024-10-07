// https://open.kattis.com/problems/rhythmflow

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int e[2000];
int a[2000];
int dp[2001][2001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> e[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);

            if (abs(a[j] - e[i]) <= 15) {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 7);
            } else if (abs(a[j] - e[i]) <= 23) {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 6);
            } else if (abs(a[j] - e[i]) <= 43) {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 4);
            } else if (abs(a[j] - e[i]) <= 102) {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 2);
            }
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}
