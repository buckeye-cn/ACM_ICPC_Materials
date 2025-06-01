// https://open.kattis.com/problems/burrowswheeler

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

long dp[18][100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;

    while (getline(cin, s)) {
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < s.size(); ++i) {
            dp[0][i] = (s[i] << 20) + i;
        }

        for (int i = 0; i < 17; ++i) {
            sort(dp[i], dp[i] + s.size());

            long rank = 0;

            for (int j = 0; j < s.size(); ++j) {
                int k = dp[i][j] & 1048575;

                rank += j && dp[i][j - 1] >> 20 < dp[i][j] >> 20;
                dp[i + 1][k] += (rank << 40) + k;

                if ((dp[i][j] & 1048575) >= 1 << i) {
                    dp[i + 1][k - (1 << i)] += rank << 20;
                } else {
                    dp[i + 1][k + s.size() - (1 << i)] += rank << 20;
                }
            }
        }

        sort(dp[17], dp[17] + s.size());

        for (int i = 0; i < s.size(); ++i) {
            int k = dp[17][i] & 1048575;

            if (k) {
                cout << s[k - 1];
            } else {
                cout << s[s.size() - 1];
            }
        }

        cout << endl;
    }

    return 0;
}
