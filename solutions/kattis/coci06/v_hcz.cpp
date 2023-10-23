// https://open.kattis.com/problems/v

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long dp[1000001];

int get_digits(long i) {
    int m = 0;

    while (i) {
        m |= 1 << (i % 10);
        i /= 10;
    }

    return m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(dp, -1, sizeof(dp));

    long x, a, b;
    string s;
    cin >> x >> a >> b >> s;

    int mask = 0;

    for (char c: s) {
        mask |= 1 << (c - '0');
    }

    long result = 0;

    for (long i = (a / 100000 * 100000 + x - 1) / x * x; i < a; i += x) {
        result -= !(~mask & get_digits(i));
    }

    for (long i = (b / 100000 * 100000 + x - 1) / x * x; i <= b; i += x) {
        result += !(~mask & get_digits(i));
    }

    for (long i = a / 100000; i < b / 100000; ++i) {
        if (!(~mask & get_digits(i))) {
            long ii = i ? (i - 1) % x + 1 : 0;

            if (dp[ii] < 0) {
                dp[ii] = 0;

                for (long j = (i * 100000 + x - 1) / x * x; j < (i + 1) * 100000; j += x) {
                    dp[ii] += !(~mask & get_digits(j));
                }
            }

            result += dp[ii];
        }
    }

    cout << result << endl;

    return 0;
}
