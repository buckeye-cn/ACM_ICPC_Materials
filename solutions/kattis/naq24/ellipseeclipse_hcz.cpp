// https://open.kattis.com/problems/ellipseeclipse

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

    double x1, y1, x2, y2, a;
    cin >> x1 >> y1 >> x2 >> y2 >> a;

    double b = sqrt(sqr(a) - sqr(x2 - x1) - sqr(y2 - y1));
    double t = atan2(y2 - y1, x2 - x1);
    double xl = 10000;
    double yl = 10000;
    double xh = -10000;
    double yh = -10000;

    for (double i = 0; i <= PI * 2; i += 1e-3) {
        double x = (x1 + x2 + b * sin(i) * sin(t) + a * cos(i) * cos(t)) / 2;
        double y = (y1 + y2 + b * sin(i) * cos(t) - a * cos(i) * sin(t)) / 2;

        xl = min(xl, x);
        yl = min(yl, y);
        xh = max(xh, x);
        yh = max(yh, y);
    }

    cout << xl << ' ' << yl << ' ' << xh << ' ' << yh << endl;

    return 0;
}
