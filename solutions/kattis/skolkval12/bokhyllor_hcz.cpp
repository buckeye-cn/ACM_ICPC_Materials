// https://open.kattis.com/problems/bokhyllor

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[21][21][21];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int a, b, c, s;
    cin >> a >> b >> c >> s;

    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            for (int k = 0; k <= c; ++k) {
                dp[i][j][k] = i || j || k ? 60 : 0;

                for (int ii = 0; ii <= i; ++ii) {
                    for (int jj = 0; jj <= j; ++jj) {
                        for (int kk = 0; kk <= k; ++kk) {
                            if (ii + 2 * jj + 3 * kk > s) break;

                            dp[i][j][k] = min(dp[i][j][k], dp[i - ii][j - jj][k - kk] + 1);
                        }
                    }
                }
            }
        }
    }

    cout << dp[a][b][c] << endl;

    return 0;
}
