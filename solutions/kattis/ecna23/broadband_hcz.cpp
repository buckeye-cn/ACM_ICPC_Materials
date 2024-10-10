// https://open.kattis.com/problems/broadband

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double xs[2000];
double cumsum1[2001];
double cumsum2[2001];
double dp[2001][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n, ap;
    double s;
    cin >> m >> n >> ap >> s;

    for (int i = 0; i < m + n; ++i) {
        cin >> xs[i];
    }

    sort(xs, xs + m + n);

    int pos = 0;

    for (int i = 0; i < m + n; ++i) {
        cumsum1[pos + 1] = cumsum1[pos] + xs[i];
        cumsum2[pos + 1] = cumsum2[pos] + xs[i] * xs[i];
        pos += 1;
    }

    for (int i = 1; i <= m + n; ++i) {
        for (int j = 0; j <= ap; ++j) {
            dp[i][j] = 1e9;
        }
    }

    for (int i = 0; i < m + n; ++i) {
        for (int j = i + 1; j <= m + n; ++j) {
            double v = cumsum2[j] - cumsum2[i] - sqr(cumsum1[j] - cumsum1[i]) / (j - i);

            for (int k = 0; k < ap; ++k) {
                dp[j][k + 1] = min(dp[j][k + 1], dp[i][k] + v);
            }
        }
    }

    cout << dp[m + n][ap] + sqr(s) * (m + n) / 4 << endl;

    return 0;
}
