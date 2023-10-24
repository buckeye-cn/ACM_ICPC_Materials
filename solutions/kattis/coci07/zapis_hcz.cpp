// https://open.kattis.com/problems/zapis

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long dp[201][201][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    string s;
    cin >> n >> s;

    for (int i = 0; i <= s.size(); ++i) {
        dp[i][i][0] = 1;
    }

    for (int i = 0; i <= s.size(); ++i) {
        for (int j = i - 2; j >= 0; j -= 2) {
            if (s[j] == '?' && s[i - 1] == '?') {
                dp[j][i][0] += (dp[j + 1][i - 1][0] + dp[j + 1][i - 1][1]) * 3;
            } else if ((s[j] == '(' || s[j] == '?') && (s[i - 1] == ')' || s[i - 1] == '?')) {
                dp[j][i][0] += dp[j + 1][i - 1][0] + dp[j + 1][i - 1][1];
            } else if ((s[j] == '[' || s[j] == '?') && (s[i - 1] == ']' || s[i - 1] == '?')) {
                dp[j][i][0] += dp[j + 1][i - 1][0] + dp[j + 1][i - 1][1];
            } else if ((s[j] == '{' || s[j] == '?') && (s[i - 1] == '}' || s[i - 1] == '?')) {
                dp[j][i][0] += dp[j + 1][i - 1][0] + dp[j + 1][i - 1][1];
            }

            for (int k = j + 2; k <= i - 2; k += 2) {
                dp[j][i][1] += (dp[j][k][0] + dp[j][k][1]) * dp[k][i][0];
            }

            if (dp[j][i][0] >= 100000) {
                dp[j][i][0] = dp[j][i][0] % 100000 + 100000;
            }

            if (dp[j][i][1] >= 100000) {
                dp[j][i][1] = dp[j][i][1] % 100000 + 100000;
            }
        }
    }

    long result = dp[0][s.size()][0] + dp[0][s.size()][1];

    if (result >= 110000) {
        cout << result % 100000 << endl;
    } else if (result >= 101000) {
        cout << "0" << result % 100000 << endl;
    } else if (result >= 100100) {
        cout << "00" << result % 100000 << endl;
    } else if (result >= 100010) {
        cout << "000" << result % 100000 << endl;
    } else if (result >= 100000) {
        cout << "0000" << result % 100000 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
