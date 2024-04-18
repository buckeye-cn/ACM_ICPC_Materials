// https://open.kattis.com/problems/1sforall

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = i;

        for (int j = 1; j * j <= i; ++j) {
            dp[i] = min(dp[i], dp[j] + dp[i - j]);

            if (i % j == 0) {
                dp[i] = min(dp[i], dp[j] + dp[i / j]);
            }
        }

        if (i / 10 >= 1 && i % 10 >= 1) dp[i] = min(dp[i], dp[i / 10] + dp[i % 10]);
        if (i / 100 >= 1 && i % 100 >= 10) dp[i] = min(dp[i], dp[i / 100] + dp[i % 100]);
        if (i / 1000 >= 1 && i % 1000 >= 100) dp[i] = min(dp[i], dp[i / 1000] + dp[i % 1000]);
        if (i / 10000 >= 1 && i % 10000 >= 1000) dp[i] = min(dp[i], dp[i / 10000] + dp[i % 10000]);
    }

    cout << dp[n] << endl;

    return 0;
}
