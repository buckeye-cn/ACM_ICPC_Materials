// https://open.kattis.com/problems/welcomeeasy

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[501][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    cin.get();

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        string s;
        getline(cin, s);

        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j <= 19; ++j) {
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= 10000;
            }

            for (int j = 0; j < 19; ++j) {
                if (s[i] == "welcome to code jam"[j]) {
                    dp[i + 1][j + 1] += dp[i][j];
                    dp[i + 1][j + 1] %= 10000;
                }
            }
        }

        cout << dp[s.size()][19] / 1000
             << dp[s.size()][19] / 100 % 10
             << dp[s.size()][19] / 10 % 10
             << dp[s.size()][19] % 10 << endl;
    }

    return 0;
}
