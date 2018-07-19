// https://open.kattis.com/problems/colorwalk

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool edge[2][16][16];
bool dp[16][65536];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(15);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int size;
        cin >> size;

        for (int color = 0; color <= 1; ++color) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    cin >> edge[color][j][k];
                }
            }
        }

        int result = 0;

        for (int qlen = 1; qlen <= size; ++qlen) {
            memset(dp, 0, sizeof(dp));

            for (bool updated = true; updated; ) {
                updated = false;

                for (int j = 0; j < size; ++j) {
                    for (int q = 0; q < 1 << qlen; ++q) {
                        if (dp[j][q]) continue;

                        int color = q & 1;

                        int rejected = true;

                        for (int k = 0; k < size; ++k) {
                            if (edge[color][j][k]) {
                                rejected &= dp[k][(q >> 1) | (1 << (qlen - 1))] || dp[k][q >> 1];
                            }
                        }

                        dp[j][q] = rejected;
                        updated |= rejected;
                    }
                }
            }

            // for (int j = 0; j < size; ++j) {
            //     for (int q = 0; q < 1 << qlen; ++q) {
            //         cerr << i << ": " << j << ' ' << q << " is " << dp[j][q] << endl;
            //     }
            // }

            bool fail = false;

            for (int q = 0; q < 1 << qlen; ++q) {
                fail |= dp[0][q];
            }

            if (!fail) {
                result = qlen;
                break;
            }
        }

        cout << result << endl;
    }

    return 0;
}
