// https://open.kattis.com/problems/mosquitoes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))
#define sqrdist(x, y) (sqr(x) + sqr(y))

using namespace std;

double cross(double a, double b, double c, double d, double e, double f) {
    return a * e + b * f + c * d - d * b - e * c - f * a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int m;
        double l, r;
        cin >> m >> l;
        r = l * 0.5 + 1e-6;

        double x[m];
        double y[m];
        double d[m];
        for (int j = 0; j < m; ++j) {
            cin >> x[j] >> y[j];
            d[j] = sqrdist(x[j], y[j]);
        }

        int best = 0;

        auto test = [&](double xx, double yy) {
            int count = 0;
            for (int j = 0; j < m; ++j) {
                if (sqrdist(x[j] - xx, y[j] - yy) < sqr(r)) {
                    count += 1;
                }
            }
            best = max(best, count);
        };

        for (int a = 0; a < m; ++a) {
            test(
                x[a],
                y[a]
            );

            for (int b = a + 1; b < m; ++b) {
                if (abs(x[a] - x[b]) > l) continue;
                if (abs(y[a] - y[b]) > l) continue;

                test(
                    0.5 * (x[a] + x[b]),
                    0.5 * (y[a] + y[b])
                );

                for (int c = b + 1; c < m; ++c) {
                    if (abs(x[a] - x[c]) > l) continue;
                    if (abs(y[a] - y[c]) > l) continue;
                    if (abs(x[b] - x[c]) > l) continue;
                    if (abs(y[b] - y[c]) > l) continue;

                    double bb = 0.5 / cross(x[a], x[b], x[c], y[a], y[b], y[c]);

                    test(
                        cross(d[a], d[b], d[c], y[a], y[b], y[c]) * bb,
                        cross(x[a], x[b], x[c], d[a], d[b], d[c]) * bb
                    );
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
