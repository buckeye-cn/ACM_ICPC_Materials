// https://open.kattis.com/problems/arbitrage

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int cur[32][32][32];
double exc[200][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int c;
        cin >> c;

        if (!c) {
            return 0;
        }

        for (int i = 0; i < c; ++i) {
            char c1, c2, c3;
            cin >> c1 >> c2 >> c3;

            cur[c1 - 64][c2 - 64][c3 - 64] = i;
        }

        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < c; ++k) {
                exc[j][k] = -INFINITY;
            }
        }

        int r;
        cin >> r;

        for (int i = 0; i < r; ++i) {
            char c1, c2, c3, c4, c5, c6;
            cin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;

            int a, b;
            cin >> a;
            cin.get();
            cin >> b;

            int j = cur[c1 - 64][c2 - 64][c3 - 64];
            int k = cur[c4 - 64][c5 - 64][c6 - 64];

            exc[j][k] = log(double(b) / a);
        }

        for (int l = 0; l < c; ++l) {
            for (int j = 0; j < c; ++j) {
                for (int k = 0; k < c; ++k) {
                    exc[j][k] = max(exc[j][k], exc[j][l] + exc[l][k]);
                }
            }
        }

        bool ok = true;

        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < c; ++k) {
                double v = exc[j][k] + exc[k][j];

                ok &= v < 1e-8;
            }
        }

        cout << (ok ? "Ok" : "Arbitrage") << endl;
    }
}
