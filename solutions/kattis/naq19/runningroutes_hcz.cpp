// https://open.kattis.com/problems/runningroutes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool route[500][500];
int dp[500][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> route[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;

        dp[i][j] = route[i][j];
    }

    for (int d = 2; d < n; ++d) {
        for (int i = 0; i < n; ++i) {
            int j = (i + d) % n;
            int i_next = (i + 1) % n;
            int j_prev = (j + n - 1) % n;

            dp[i][j] = 0;

            for (int k = i; k != j; k = (k + 1) % n) {
                int l = (k + 1) % n;

                dp[i][j] = max(dp[i][j], dp[i][k] + dp[l][j]);
            }

            if (route[i][j]) {
                dp[i][j] = max(dp[i][j], dp[i_next][j_prev] + 1);
            }
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cerr << dp[i][j] << '\t';
    //     }
    //     cerr << endl;
    // }

    cout << dp[1][0] << endl;

    return 0;
}
