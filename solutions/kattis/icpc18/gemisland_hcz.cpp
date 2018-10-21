// https://open.kattis.com/problems/gemisland

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double logfrac[1001];
double c[1001][1001];
double s[501][501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    logfrac[0] = 0;

    for (int i = 1; i <= 1000; ++i) {
        logfrac[i] = logfrac[i - 1] + log(i);
    }

    for (int i = 0; i <= 1000; ++i) {
        for (int j = 0; j <= i; ++j) {
            c[i][j] = exp(logfrac[i] - logfrac[j] - logfrac[i - j]);
        }
    }

    int n, d, r;
    cin >> n >> d >> r;

    for (int i = 1; i <= r; ++i) {
        for (int j = 0; j <= d; ++j) {
            s[i][j] = (i + j) * c[i + j - 1][j];
        }
    }

    for (int i = r + 1; i <= n; ++i) {
        for (int j = 0; j <= d; ++j) {
            s[i][j] = c[i + j - 1][j] * r;

            for (int k = i - j; k < i; ++k) {
                s[i][j] += c[i][k] * s[i - k][j - i + k];
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 0; j <= d; ++j) {
    //         cerr << i << ' ' << j << '\t'
    //             << s[i][j] << ' ' << s[i][j] / c[i + j - 1][j] << endl;
    //     }
    // }

    cout << s[n][d] / c[n + d - 1][d] << endl;

    return 0;
}
