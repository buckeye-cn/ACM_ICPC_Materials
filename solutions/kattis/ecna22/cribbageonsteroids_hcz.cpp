// https://open.kattis.com/problems/cribbageonsteroids

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[14];
long dp[16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;

        if (c == 'A') {
            v[1] += 1;
        } else if (c == 'T') {
            v[10] += 1;
        } else if (c == 'J') {
            v[11] += 1;
        } else if (c == 'Q') {
            v[12] += 1;
        } else if (c == 'K') {
            v[13] += 1;
        } else {
            v[c - '0'] += 1;
        }
    }

    dp[0] = 1;

    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < v[i]; ++j) {
            for (int k = 15; k >= min(i, 10); --k) {
                dp[k] += dp[k - min(i, 10)];
            }
        }
    }

    long result = 2 * dp[15];
    int nn = 0;
    long curr = 1;

    for (int i = 1; i <= 13; ++i) {
        result += v[i] * (v[i] - 1);

        if (v[i]) {
            nn += 1;
            curr *= v[i];
        } else {
            if (nn >= 3) {
                result += nn * curr;
            }

            nn = 0;
            curr = 1;
        }
    }

    if (nn >= 3) {
        result += nn * curr;
    }

    cout << result << endl;

    return 0;
}
