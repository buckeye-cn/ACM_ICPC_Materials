// https://open.kattis.com/problems/celebritysplit

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int value[24];

int pos[25];
int dp[1 << 25][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        int sum = 0;

        for (int i = 0; i < n; ++i) {
            cin >> value[i];

            sum += value[i];
        }

        int p1 = 0;
        int p2 = 0;
        int pp = 1;

        for (int i = 0; i < n; ++i) {
            pos[i] = pp;

            while (true) {
                if (p2 < pos[i]) {
                    if (dp[p2][0] + value[i] > dp[p1][0]) {
                        if ((dp[p2][0] + value[i]) * 2 <= sum) {
                            dp[pp][0] = dp[p2][0] + value[i];
                            dp[pp][1] = dp[p2][1] + (1 << i);
                            pp += 1;
                        }

                        p2 += 1;

                        continue;
                    }
                }

                if (p1 < pos[i]) {
                    dp[pp][0] = dp[p1][0];
                    dp[pp][1] = dp[p1][1];
                    pp += 1;

                    p1 += 1;

                    continue;
                }

                break;
            }
        }

        for (int i = pos[n - 1]; i < pp; ++i) {
            for (int j = i; dp[j][0] == dp[i][0]; ++j) {
                if (dp[j][1] & dp[i][1]) continue;

                cout << sum - dp[i][0] - dp[j][0] << endl;

                goto out;
            }
        }

        out:;
    }
}
