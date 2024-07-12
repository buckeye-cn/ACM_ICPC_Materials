// https://open.kattis.com/problems/convexhullextension

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))
#define sign(x) (((x) > 1e-10) - ((x) < -1e-10))

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

long int_points(long x1, long y1, long x2, long y2, long x3, long y3, long x4, long y4) {
    long result = abs(
        x1 * y2 + x2 * y3 + x3 * y4 + x4 * y1
        - x1 * y4 - x4 * y3 - x3 * y2 - x2 * y1
    ) + 2;

    if (x1 == x2) {
        result -= abs(y2 - y1);
    } else if (y1 == y2) {
        result -= abs(x2 - x1);
    } else {
        result -= gcd(abs(x2 - x1), abs(y2 - y1));
    }

    if (x2 == x3) {
        result -= abs(y3 - y2);
    } else if (y2 == y3) {
        result -= abs(x3 - x2);
    } else {
        result -= gcd(abs(x3 - x2), abs(y3 - y2));
    }

    if (x3 == x4) {
        result -= abs(y4 - y3);
    } else if (y3 == y4) {
        result -= abs(x4 - x3);
    } else {
        result -= gcd(abs(x4 - x3), abs(y4 - y3));
    }

    if (x4 == x1) {
        result -= abs(y1 - y4);
    } else if (y4 == y1) {
        result -= abs(x1 - x4);
    } else {
        result -= gcd(abs(x1 - x4), abs(y1 - y4));
    }

    return result / 2;
}

double double_area(double x1, double y1, double x2, double y2, double x3, double y3) {
    return x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x3 * y2 - x2 * y1;
}

bool within(
    double x, double y,
    double x1, double y1, double x2, double y2, double x3, double y3
) {
    int d1 = sign(((x - x1) * (y2 - y1) - (y - y1) * (x2 - x1)) / (sqr(y2 - y1) + sqr(x2 - x1)));
    int d2 = sign(((x - x2) * (y3 - y2) - (y - y2) * (x3 - x2)) / (sqr(y3 - y2) + sqr(x3 - x2)));
    int d3 = sign(((x - x3) * (y1 - y3) - (y - y3) * (x1 - x3)) / (sqr(y1 - y3) + sqr(x1 - x3)));

    return d1 && d1 == d2 && d2 == d3;
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

long x[100];
long y[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        x[n + i] = x[i];
        y[n + i] = y[i];
    }

    long result = 0;

    for (int i = 0; i < n; ++i) {
        if (x[i] == x[i + 1] && x[i + 2] == x[i + 3]) {
            if (abs(x[i + 2] - x[i]) >= 2) {
                cout << "infinitely many" << endl;

                return 0;
            }

            continue;
        }

        if (y[i] == y[i + 1] && y[i + 2] == y[i + 3]) {
            if (abs(y[i + 2] - y[i]) >= 2) {
                cout << "infinitely many" << endl;

                return 0;
            }

            continue;
        }

        if (
            x[i] != x[i + 1]
            && y[i] != y[i + 1]
            && x[i + 2] != x[i + 3]
            && y[i + 2] != y[i + 3]
            && (x[i + 1] - x[i]) * (y[i + 3] - y[i + 2]) == (x[i + 3] - x[i + 2]) * (y[i + 1] - y[i])
        ) {
            if (abs(double_area(x[i], y[i], x[i + 1], y[i + 1], x[i + 2], y[i + 2])) > gcd(abs(x[i] - x[i + 1]), abs(y[i] - y[i + 1]))) {
                cout << "infinitely many" << endl;

                return 0;
            }

            continue;
        }

        double xx;
        double yy;

        intersect(xx, yy, x[i], y[i], x[i + 1], y[i + 1], x[i + 3], y[i + 3], x[i + 2], y[i + 2]);

        if (double_area(x[i + 1], y[i + 1], xx, yy, x[i + 2], y[i + 2]) < 0) {
            cout << "infinitely many" << endl;

            return 0;
        }

        long p1 = floor(sqrt(sqr(xx - x[i + 1]) + sqr(yy - y[i + 1])) / sqrt(sqr(x[i + 1] - x[i]) + sqr(y[i + 1] - y[i]) + 1));
        long p2 = floor(sqrt(sqr(xx - x[i + 2]) + sqr(yy - y[i + 2])) / sqrt(sqr(x[i + 2] - x[i + 3]) + sqr(y[i + 2] - y[i + 3]) + 1));
        long x1 = x[i + 1] + p1 * (x[i + 1] - x[i]);
        long y1 = y[i + 1] + p1 * (y[i + 1] - y[i]);
        long x2 = x[i + 2] + p2 * (x[i + 2] - x[i + 3]);
        long y2 = y[i + 2] + p2 * (y[i + 2] - y[i + 3]);

        if (p1 || p2) {
            result += int_points(x[i + 1], y[i + 1], x1, y1, x2, y2, x[i + 2], y[i + 2]);

            if (x1 == x2) {
                result += abs(y2 - y1) - 1;
            } else if (y1 == y2) {
                result += abs(x2 - x1) - 1;
            } else {
                result += gcd(abs(x2 - x1), abs(y2 - y1)) - 1;
            }
        }

        for (long x3 = min(min(x1, x2), long(ceil(xx))); x3 <= max(max(x1, x2), long(floor(xx))); ++x3) {
            for (long y3 = min(min(y1, y2), long(ceil(yy))); y3 <= max(max(y1, y2), long(floor(yy))); ++y3) {
                result += within(x3, y3, x1, y1, xx, yy, x2, y2);
            }
        }
    }

    cout << result << endl;

    return 0;
}
