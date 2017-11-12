// https://open.kattis.com/problems/imperfectgps

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int n, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> t;

    double x0, y0;
    int tt0;
    double s = 0;
    double gps_s = 0;

    cin >> x0 >> y0 >> tt0;

    double xg, yg;
    xg = x0;
    yg = y0;

    for (int i = 1; i < n; ++i) {
        double x, y;
        int tt;

        cin >> x >> y >> tt;

        s += sqrt(sqr(x - x0) + sqr(y - y0));

        double dx = (x - x0) / (tt - tt0);
        double dy = (y - y0) / (tt - tt0);

        for (; tt0 < tt; ++tt0) {
            if (tt0 % t == 0) {
                gps_s += sqrt(sqr(x0 - xg) + sqr(y0 - yg));
                xg = x0;
                yg = y0;
            }

            x0 += dx;
            y0 += dy;
        }
    }

    if (xg != x0 || yg != y0) {
        gps_s += sqrt(sqr(xg - x0) + sqr(yg - y0));
    }

    // cerr << s << ' ' << gps_s << endl;
    cout << 100 * abs(gps_s - s) / s << endl;

    return 0;
}
