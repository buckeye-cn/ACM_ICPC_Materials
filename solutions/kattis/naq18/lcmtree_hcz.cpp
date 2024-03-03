// https://open.kattis.com/problems/lcmtree

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

long v[25];
int dup[25];
int duppair[25][25];
int lcmn[25];
int lcmi[25][600][2];
long dp[16777217];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> v[i];

        for (int j = i - 1; j >= 0; --j) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        dup[i] = 1;

        for (int j = 0; j < i; ++j) {
            dup[i] += v[j] == v[i];
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (v[i] == v[j]) {
                duppair[i][j] = dup[i] * dup[j] / 2;
            } else {
                duppair[i][j] = dup[i] * dup[j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < j; ++k) {
                if (v[j] == v[k] && j != k + 1) continue;

                if (v[j] * v[k] == v[i] * gcd(v[j], v[k])) {
                    lcmi[i][lcmn[i]][0] = j;
                    lcmi[i][lcmn[i]][1] = k;
                    lcmn[i] += 1;
                }
            }
        }
    }

    dp[1 << (n - 1)] = dup[n - 1];

    for (int i = n - 1; i >= 0; --i) {
        for (int mask = min((2 << i) - 1, 1 << (n - 1)); mask >= 1 << i; --mask) {
            if (!dp[mask]) continue;

            dp[mask] %= MOD;

            for (int j = 0; j < lcmn[i]; ++j) {
                int i1 = lcmi[i][j][0];
                int i2 = lcmi[i][j][1];

                if (mask & (1 << i1)) continue;
                if (mask & (1 << i2)) continue;

                int newmask = mask;

                if (v[i1] == v[i1 + 1] && !(newmask & (2 << i1))) continue;
                newmask ^= 1 << i1;
                if (v[i2] == v[i2 + 1] && !(newmask & (2 << i2))) continue;
                newmask ^= 1 << i2;
                newmask ^= 1 << i;
                if (newmask < 1 << (i - 1)) continue;

                dp[newmask] += dp[mask] * duppair[i1][i2];
            }

            int newmask = mask;

            newmask ^= 1 << i;
            if (newmask < 1 << (i - 1)) continue;

            dp[newmask] += dp[mask];
        }
    }

    cout << dp[0] % MOD << endl;

    return 0;
}
