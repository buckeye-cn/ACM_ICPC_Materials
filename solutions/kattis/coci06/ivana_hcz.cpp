// https://open.kattis.com/problems/ivana

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;

        dp[1][i] = v & 1;
    }

    for (int i = 2; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = max(
                dp[1][(j + i - 1) % n] - dp[i - 1][j],
                dp[1][j] - dp[i - 1][(j + 1) % n]
            );
        }
    }

    int result = 0;

    for (int i = 0; i < n; ++i) {
        result += dp[1][i] > dp[n - 1][(i + 1) % n];
    }

    cout << result << endl;

    return 0;
}
