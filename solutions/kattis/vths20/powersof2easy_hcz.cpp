// https://open.kattis.com/problems/powersof2easy

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int am[20][10];
long dp[21][21][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string n;
    int e;
    cin >> n >> e;

    string ee = to_string(1l << e);

    for (int i = 0; i < ee.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            if (strncmp(ee.data(), ee.data() + i - j, j) == 0) {
                am[i][ee[j] - '0'] = j + 1;
            }
        }
    }

    // for (int i = 0; i < 20; ++i) {
    //     for (int j = 0; j < 10; ++j) {
    //         if (am[i][j]) {
    //             cerr << i << ' ' << j << ' ' << am[i][j] << endl;
    //         }
    //     }
    // }

    dp[0][0][1] = 1;

    for (int i = 0; i < n.size(); ++i) {
        for (int j = 0; j < ee.size(); ++j) {
            for (int k = 0; k < 10; ++k) {
                dp[i + 1][am[j][k]][0] += dp[i][j][0];
            }

            for (int k = 0; k < n[i] - '0'; ++k) {
                dp[i + 1][am[j][k]][0] += dp[i][j][1];
            }

            dp[i + 1][am[j][n[i] - '0']][1] += dp[i][j][1];
        }

        dp[i + 1][ee.size()][0] += dp[i][ee.size()][0] * 10 + dp[i][ee.size()][1] * (n[i] - '0');
        dp[i + 1][ee.size()][1] += dp[i][ee.size()][1];
    }

    cout << dp[n.size()][ee.size()][0] + dp[n.size()][ee.size()][1] << endl;

    return 0;
}
