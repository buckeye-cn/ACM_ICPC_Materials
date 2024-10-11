// https://open.kattis.com/problems/countcircuits

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const int BASE = 402;
const int CAP = BASE * BASE;

using namespace std;

int ii[CAP];
long xy_value[CAP];
long dp[2][CAP];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    xy_value[0] = CAP / 2;
    dp[0][0] = 1;

    int tot = 1;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        int delta = x * BASE + y;
        int old_tot = tot;

        for (int j = 0; j < old_tot; ++j) {
            dp[~i & 1][j] += dp[i & 1][j];

            if (ii[xy_value[j] + delta]) {
                dp[~i & 1][ii[xy_value[j] + delta]] += dp[i & 1][j];
            } else if (xy_value[j] + delta == CAP / 2) {
                dp[~i & 1][0] += dp[i & 1][j];
            } else {
                xy_value[tot] = xy_value[j] + delta;
                dp[~i & 1][tot] += dp[i & 1][j];
                ii[xy_value[tot]] = tot;
                tot += 1;
            }

            dp[i & 1][j] = 0;
        }
    }

    cout << (dp[n & 1][0] - 1) << endl;

    return 0;
}
