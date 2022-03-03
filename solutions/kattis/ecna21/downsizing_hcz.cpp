// https://open.kattis.com/problems/downsizing

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double ox, oy, r;
    cin >> ox >> oy >> r;

    if (r == 0) {
        cout << 0 << endl;

        return 0;
    }

    int n;
    cin >> n;

    double x[n];
    double y[n];

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        x[i] = (x[i] - ox) / r;
        y[i] = (y[i] - oy) / r;
    }

    double s = 0;

    for (int i = 0; i < n; ++i) {
        double x1 = x[i];
        double y1 = y[i];
        double x2 = x[(i + 1) % n];
        double y2 = y[(i + 1) % n];

        double px = x1;
        double py = y1;
        double pr = sqrt(sqr(px) + sqr(py));
        double pa = atan2(py, px);

        for (double p = 1e-5; p <= 1 + 5e-6; p += 1e-5) {
            double nx = x1 * (1 - p) + x2 * p;
            double ny = y1 * (1 - p) + y2 * p;
            double nr = sqrt(sqr(nx) + sqr(ny));
            double na = atan2(ny, nx);

            if (pa < na - PI) {
                pa += 2 * PI;
            } else if (pa > na + PI) {
                pa -= 2 * PI;
            }

            s += (na - pa) / sqr(nr + pr);

            px = nx;
            py = ny;
            pr = nr;
            pa = na;
        }
    }

    cout << 2 * abs(s) * sqr(r) << endl;

    return 0;
}
