// https://open.kattis.com/problems/frogger

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long cars[22][50][50];
long dp[22][50][50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int x, n, m;
        cin >> x >> n >> m;

        n += 2;

        int fpos;
        int gpos;

        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                char c;
                cin >> c;

                for (int l = 0; l < m; ++l) {
                    if ((n - j) & 1) {
                        cars[j][(k + m - l) % m][l] = c == 'X';
                    } else {
                        cars[j][(k + l) % m][l] = c == 'X';
                    }
                }

                if (c == 'F') fpos = k;
                if (c == 'G') gpos = k;
            }
        }

        memset(dp, 0, sizeof(dp));
        dp[n - 1][fpos][0] = true;

        int step = 1;
        for (; step <= x; ++step) {
            int last_l = (step - 1) % m;
            int l = step % m;

            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    if (cars[j][k][l]) continue;

                    dp[j][k][l] |= dp[j][k][last_l];
                    if (j - 1 >= 0) dp[j][k][l] |= dp[j - 1][k][last_l];
                    if (j + 1 < n) dp[j][k][l] |= dp[j + 1][k][last_l];
                    if (k - 1 >= 0) dp[j][k][l] |= dp[j][k - 1][last_l];
                    if (k + 1 < m) dp[j][k][l] |= dp[j][k + 1][last_l];
                }
            }

            if (dp[0][gpos][l]) break;
        }

        // for (int l = 0; l < m; ++l) {
        //     for (int j = 0; j < n; ++j) {
        //         for (int k = 0; k < m; ++k) {
        //             if (cars[j][k][l]) {
        //                 cerr << "\tcar";
        //             } else {
        //                 cerr << '\t' << dp[j][k][l];
        //             }
        //         }
        //         cerr << endl;
        //     }
        //     cerr << endl;
        // }

        if (step < x + 1) {
            cout << "The minimum number of turns is " << step << '.' << endl;
        } else {
            cout << "The problem has no solution." << endl;
        }
    }


    return 0;
}
