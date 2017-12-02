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
    cout.precision(15);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int m;
        double r;
        cin >> m >> r;
        r = r * 0.5 + 1e-6;

        double x[m];
        double y[m];
        for (int j = 0; j < m; ++j) {
            cin >> x[j] >> y[j];
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
                test(
                    0.5 * (x[a] + x[b]),
                    0.5 * (y[a] + y[b])
                );

                for (int c = b + 1; c < m; ++c) {
                    double bb = cross(x[a], x[b], x[c], y[a], y[b], y[c]);

                    test(
                        0.5 * cross(sqrdist(x[a], y[a]), sqrdist(x[b], y[b]), sqrdist(x[c], y[c]), y[a], y[b], y[c]) / bb,
                        0.5 * cross(x[a], x[b], x[c], sqrdist(x[a], y[a]), sqrdist(x[b], y[b]), sqrdist(x[c], y[c])) / bb
                    );
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
