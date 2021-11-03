// https://open.kattis.com/problems/oreperationsresearch

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int gcd(int y, int x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int a[50];
int b[50];
int a_cum[100];
int b_cum[100];

bool loop[2000001];
bool dp[101][50][50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int r, s, n;
    cin >> r >> s >> n;

    for (int i = 0; i < r; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i < 2 * r; ++i) {
        a_cum[i] = a[(i - 1) % r] + a_cum[i - 1];
    }

    for (int i = 0; i < s; ++i) {
        cin >> b[i];
    }

    for (int i = 1; i < 2 * s; ++i) {
        b_cum[i] = b[(i - 1) % s] + b_cum[i - 1];
    }

    int ax = a_cum[r];
    int bx = b_cum[s];
    int bound = min(ax * bx / gcd(ax, bx), 2000001);

    for (int i = 0; i * ax < bound; ++i) {
        for (int j = 0; i * ax + j * bx < bound; ++j) {
            loop[i * ax + j * bx] = true;
        }
    }

    for (int i = bound; i <= 2000000; ++i) {
        loop[i] = loop[i - bound];
    }

    dp[0][0][0] = true;

    for (int i = 1; i <= n; ++i) {
        int c;
        cin >> c;

        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < s; ++k) {
                if (dp[i - 1][j][k]) {
                    for (int jj = j; jj < j + r; ++jj) {
                        for (int kk = k; kk < k + s; ++kk) {
                            int delta = a_cum[jj] - a_cum[j] + b_cum[kk] - b_cum[k];

                            if (c >= delta && loop[c - delta]) {
                                dp[i][jj >= r ? jj - r : jj][kk >= s ? kk - s : kk] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int j = 0; j < r; ++j) {
        for (int k = 0; k < s; ++k) {
            if (dp[n][j][k]) {
                cout << "Yes" << endl;

                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}
