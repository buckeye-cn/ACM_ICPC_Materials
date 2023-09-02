// https://open.kattis.com/problems/pickingupsteam

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double x[1001];
double y[1001];

void intersect(
    double &x, double &y,
    double px1, double py1, double px2, double py2,
    double qx1, double qy1, double qx2, double qy2
) {
    double px = px2 - px1;
    double py = py2 - py1;
    double qx = qx2 - qx1;
    double qy = qy2 - qy1;

    double pxqy = px * qy;
    double pyqx = py * qx;
    double pxqx = px * qx;
    double pyqy = py * qy;

    x = (py1 * pxqx - px1 * pyqx - qy1 * pxqx + qx1 * pxqy) / (pxqy - pyqx);
    y = (px2 * pyqy - py2 * pxqy - qx2 * pyqy + qy2 * pyqx) / (pyqx - pxqy);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }

    double cx, sx, sy, r, dx, dy, v;
    cin >> cx >> sx >> sy >> r >> dx >> dy >> v;

    double d = sqrt(sqr(dx) + sqr(dy));

    dx /= d;
    dy /= d;

    double cy;
    int pl, pr;

    for (int i = 0; i < n; ++i) {
        if (cx <= x[i + 1]) {
            cy = ((cx - x[i]) * y[i + 1] + (x[i + 1] - cx) * y[i]) / (x[i + 1] - x[i]);
            pl = max(i - (cx == x[i]), 0);
            pr = min(i + 1 + (cx == x[i + 1]), n);
            break;
        }
    }

    for (int i = pl - 1; i >= 0; --i) {
        if ((cx - x[i]) * (cy - y[pl]) > (cx - x[pl]) * (cy - y[i])) {
            if (x[pl] > x[i + 1]) {
                pl -= 1;
                intersect(x[pl], y[pl], cx, cy, x[pl + 1], y[pl + 1], x[i + 1], y[i + 1], x[i], y[i]);
            }

            pl -= 1;
            x[pl] = x[i];
            y[pl] = y[i];
        }
    }

    if (x[pl] > x[0]) {
        pl -= 1;
        intersect(x[pl], y[pl], cx, cy, x[pl + 1], y[pl + 1], x[0], 0, x[0], 1);
    }

    for (int i = pr + 1; i <= n; ++i) {
        if ((x[i] - cx) * (y[pr] - cy) < (x[pr] - cx) * (y[i] - cy)) {
            if (x[pr] < x[i - 1]) {
                pr += 1;
                intersect(x[pr], y[pr], cx, cy, x[pr - 1], y[pr - 1], x[i - 1], y[i - 1], x[i], y[i]);
            }

            pr += 1;
            x[pr] = x[i];
            y[pr] = y[i];
        }
    }

    if (x[pr] < x[n]) {
        pr += 1;
        intersect(x[pr], y[pr], cx, cy, x[pr - 1], y[pr - 1], x[n], 0, x[n], 1);
    }

    double k = 0;

    for (int level = 20; level >= 0; --level) {
        double rr = r + (1 << level) * 1e-3;

        while (true) {
            double xx = sx + k * dx;
            double yy = sy + k * dy;

            if (xx < x[pl] - r || xx > x[pr] + r) break;

            bool ok = false;

            for (int i = pl; i <= pr && !ok; ++i) {
                ok = sqr(x[i] - xx) + sqr(y[i] - yy) < sqr(rr);
            }

            for (int i = pl; i < pr && !ok; ++i) {
                double xx1, yy1;
                intersect(xx1, yy1, xx, yy, xx + (y[i + 1] - y[i]), yy - (x[i + 1] - x[i]), x[i], y[i], x[i + 1], y[i + 1]);

                ok = xx1 >= x[i] && xx1 <= x[i + 1] && sqr(xx1 - xx) + sqr(yy1 - yy) < sqr(rr);
            }

            if (ok) {
                if (level) break;

                cout << k / v << endl;

                return 0;
            }

            k += rr - r;
            k *= 1.0001;
        }
    }

    cout << -1 << endl;

    return 0;
}
