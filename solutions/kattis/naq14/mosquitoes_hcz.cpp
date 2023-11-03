// https://open.kattis.com/problems/mosquitoes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double double_area(double x1, double y1, double x2, double y2, double x3, double y3) {
    return x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x3 * y2 - x2 * y1;
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
            d[j] = sqr(x[j]) + sqr(y[j]);
        }

        int best = 0;

        auto test = [&](double xx, double yy) {
            int count = 0;
            for (int j = 0; j < m; ++j) {
                if (sqr(x[j] - xx) + sqr(y[j] - yy) < sqr(r)) {
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

                    double bb = 0.5 / double_area(x[a], y[a], x[b], y[b], x[c], y[c]);

                    test(
                        double_area(d[a], y[a], d[b], y[b], d[c], y[c]) * bb,
                        double_area(x[a], d[a], x[b], d[b], x[c], d[c]) * bb
                    );
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
