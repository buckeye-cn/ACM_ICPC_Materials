// https://open.kattis.com/problems/barktree

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))
#define sign(x) (((x) > 1e-10) - ((x) < -1e-10))

const double PI = acos(-1);

using namespace std;

int n, m;
double nx[50];
double ny[50];
double mx[50];
double my[50];

int k;
double kx[2501];
double ky[2501];
double k_angle[2501];
double k_len[2501];
double max_len;

bool within(
    double x, double y,
    double x1, double y1, double x2, double y2, double x3, double y3
) {
    int d1 = sign(((x - x1) * (y2 - y1) - (y - y1) * (x2 - x1)) / sqrt(sqr(y2 - y1) + sqr(x2 - x1)));
    int d2 = sign(((x - x2) * (y3 - y2) - (y - y2) * (x3 - x2)) / sqrt(sqr(y3 - y2) + sqr(x3 - x2)));
    int d3 = sign(((x - x3) * (y1 - y3) - (y - y3) * (x1 - x3)) / sqrt(sqr(y1 - y3) + sqr(x1 - x3)));

    return d1 && d1 == d2 && d2 == d3;
}

double reldot(
    double x, double y,
    double x1, double y1, double x2, double y2
) {
    return ((x1 - x) * (x2 - x) + (y1 - y) * (y2 - y))
        / sqrt(sqr(x2 - x) + sqr(y2 - y));
}

double angle(
    double x, double y,
    double x1, double y1, double x2, double y2
) {
    double result = atan2(y2 - y, x2 - x) - atan2(y1 - y, x1 - x);

    if (result < PI) result += 2 * PI;
    if (result > PI) result -= 2 * PI;

    return result;
}

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

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> nx[i] >> ny[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> mx[i] >> my[i];
    }

    double x = 0;
    double y = 0;

    for (int i = 0; i < n; ++i) {
        while (true) {
            int best = -1;
            double best_dot = -INFINITY;

            for (int j = 0; j < m; ++j) {
                if (!within(
                    mx[j], my[j],
                    kx[k], ky[k], x, y, nx[i], ny[i]
                )) continue;

                double d = reldot(
                    kx[k], ky[k],
                    x, y, mx[j], my[j]
                );

                if (best_dot < d) {
                    best = j;
                    best_dot = d;
                }
            }

            double mid_x, mid_y;
            if (best >= 0) {
                intersect(
                    mid_x, mid_y,
                    kx[k], ky[k], mx[best], my[best],
                    x, y, nx[i], ny[i]
                );
            } else {
                mid_x = nx[i];
                mid_y = ny[i];
            }

            double rotation = angle(
                kx[k], ky[k],
                x, y, mid_x, mid_y
            );

            if (k > 0 && sign(k_angle[k]) != sign(k_angle[k] + rotation)) {
                intersect(
                    mid_x, mid_y,
                    kx[k - 1], ky[k - 1], kx[k], ky[k],
                    x, y, nx[i], ny[i]
                );

                k -= 1;

                x = mid_x;
                y = mid_y;

                // cerr << "pop " << x << ' ' << y << endl;
            } else {
                k_angle[k] += rotation;

                if (best >= 0) {
                    k += 1;
                    kx[k] = mx[best];
                    ky[k] = my[best];
                    k_angle[k] = sign(rotation) * 1e-6;
                    k_len[k] = k_len[k - 1] + sqrt(sqr(kx[k] - kx[k - 1]) + sqr(ky[k] - ky[k - 1]));

                    x = mid_x;
                    y = mid_y;

                    // cerr << "push " << x << ' ' << y << ' ' << best << endl;
                } else {
                    max_len = max(max_len, k_len[k] + sqrt(sqr(nx[i] - kx[k]) + sqr(ny[i] - ky[k])));

                    x = nx[i];
                    y = ny[i];

                    // cerr << "reach " << x << ' ' << y << endl;

                    break;
                }
            }
        }
    }

    printf("%.2f\n", max_len);

    return 0;
}
