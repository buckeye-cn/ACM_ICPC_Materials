// https://open.kattis.com/problems/gamblinggame

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

pair<long, long> add(pair<long, long> x, pair<long, long> y) {
    long v = x.first * y.second + x.second * y.first;
    long d = x.second * y.second;
    long g = gcd(v, d);

    return {v / g, d / g};
}

pair<long, long> mul(pair<long, long> x, pair<long, long> y) {
    long v = x.first * y.first;
    long d = x.second * y.second;
    long g = gcd(v, d);

    return {v / g, d / g};
}

pair<long, long> dp[40][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n, p;
    cin >> m >> n >> p;

    if (!n && !p) {
        cout << "1/1" << endl;

        return 0;
    }

    if (!n || !p) {
        cout << "0/1" << endl;

        return 0;
    }

    for (int i = 0; i <= p; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = {0, 1};
        }
    }

    dp[0][0] = {1, 1};

    for (int i = 0; i < p; ++i) {
        long bb = m - i;

        for (int j = 0; j < n; ++j) {
            long gg = 2 * (n - j);

            dp[i + 1][j + 1] = add(dp[i + 1][j + 1], mul(dp[i][j], {gg, bb}));
            dp[i + 1][j] = add(dp[i + 1][j], mul(dp[i][j], {bb - gg, bb}));
        }
    }

    pair<long, long> res = mul(dp[p - 1][n - 1], {2, (m - p + 1)});

    cout << res.first << '/' << res.second << endl;

    return 0;
}
