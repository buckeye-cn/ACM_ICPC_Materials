// https://open.kattis.com/problems/itsabouttime

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long r, s, h;
    cin >> r >> s >> h;

    double d = 2 * PI * r / s / h;

    d = abs(d - round(d));

    double best = d;
    long best_i = 250;
    long best_j = 2;
    long best_k = 2;

    for (long i = 2; i <= 250 && i * d < 1; ++i) {
        double e = 1 - i * d;

        for (long j = 2; i * j <= 500 && j * e < 1; ++j) {
            double f = 1 - j * e;
            double k0 = floor(1 / f);

            for (long k = k0; i * j * k <= 1000 && k <= k0 + 1; ++k) {
                double g = 1 - k * f;
                double err = abs(g / (i * j * k));

                if (best > err) {
                    best = err;
                    best_i = i;
                    best_j = j;
                    best_k = k;
                }
            }
        }
    }

    cout << best_i << ' ' << best_i * best_j << ' ' << best_i * best_j * best_k << endl;

    return 0;
}
