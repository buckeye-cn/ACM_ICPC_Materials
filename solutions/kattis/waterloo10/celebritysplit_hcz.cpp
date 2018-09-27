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
pair<int, int> dp[1 << 25];

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
                    if (dp[p2].first + value[i] > dp[p1].first) {
                        if ((dp[p2].first + value[i]) * 2 <= sum) {
                            dp[pp].first = dp[p2].first + value[i];
                            dp[pp].second = dp[p2].second + (1 << i);
                            pp += 1;
                        }

                        p2 += 1;

                        continue;
                    }
                }

                if (p1 < pos[i]) {
                    dp[pp].first = dp[p1].first;
                    dp[pp].second = dp[p1].second;
                    pp += 1;

                    p1 += 1;

                    continue;
                }

                break;
            }
        }

        for (int i = pos[n - 1]; i < pp; ++i) {
            for (int j = i; dp[j].first == dp[i].first; ++j) {
                if (dp[j].second & dp[i].second) continue;

                cout << sum - dp[i].first - dp[j].first << endl;

                goto out;
            }
        }

        out:;
    }
}
