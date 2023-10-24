// https://open.kattis.com/problems/dobra

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// dp[i][nil/L][nil/1a/2a/1b/2b]
long dp[101][2][5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    dp[0][0][0] = 1;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '_') {
            dp[i + 1][0][1] = (dp[i][0][0] + dp[i][0][3] + dp[i][0][4]) * 5;
            dp[i + 1][0][2] = dp[i][0][1] * 5;
            dp[i + 1][0][3] = (dp[i][0][0] + dp[i][0][1] + dp[i][0][2]) * 20;
            dp[i + 1][0][4] = dp[i][0][3] * 20;
            dp[i + 1][1][1] = (dp[i][1][3] + dp[i][1][4]) * 5;
            dp[i + 1][1][2] = dp[i][1][1] * 5;
            dp[i + 1][1][3] = dp[i][0][0] + dp[i][0][1] + dp[i][0][2] + (dp[i][1][1] + dp[i][1][2]) * 21;
            dp[i + 1][1][4] = dp[i][0][3] + dp[i][1][3] * 21;
        } else if (s[i] == 'L') {
            dp[i + 1][1][3] = dp[i][0][0] + dp[i][0][1] + dp[i][0][2] + dp[i][1][1] + dp[i][1][2];
            dp[i + 1][1][4] = dp[i][0][3] + dp[i][1][3];
        } else if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
            dp[i + 1][0][1] = dp[i][0][0] + dp[i][0][3] + dp[i][0][4];
            dp[i + 1][0][2] = dp[i][0][1];
            dp[i + 1][1][1] = dp[i][1][3] + dp[i][1][4];
            dp[i + 1][1][2] = dp[i][1][1];
        } else {
            dp[i + 1][0][3] = dp[i][0][0] + dp[i][0][1] + dp[i][0][2];
            dp[i + 1][0][4] = dp[i][0][3];
            dp[i + 1][1][3] = dp[i][1][1] + dp[i][1][2];
            dp[i + 1][1][4] = dp[i][1][3];
        }
    }

    cout << dp[s.size()][1][1] + dp[s.size()][1][2] + dp[s.size()][1][3] + dp[s.size()][1][4] << endl;

    return 0;
}
