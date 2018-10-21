// https://open.kattis.com/problems/trickshot

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

bool collide(double x1, double y1, double x2, double y2, double x, double y, double r) {
    double d_sqr = sqr(x2 - x1) + sqr(y2 - y1);
    double dot = (x - x1) * (x2 - x1) + (y - y1) * (y2 - y1);

    double vx = x1 + (x2 - x1) * dot / d_sqr;
    double vy = y1 + (y2 - y1) * dot / d_sqr;

    double distance = sqrt(sqr(x - vx) + sqr(y - vy));

    return distance <= 2 * r && vy > min(y1, y2) && vy < max(y1, y2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double w, l, r, h;
    double x1, y1, x2, y2, x3, y3;
    cin >> w >> l >> r >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> h;

    double d2 = sqrt(sqr(0 - x2) + sqr(l - y2));
    double x02 = 0 - (0 - x2) / d2 * (d2 + 2 * r);
    double y02 = l - (l - y2) / d2 * (d2 + 2 * r);

    double d3 = sqrt(sqr(w - x3) + sqr(l - y3));
    double x13 = w - (w - x3) / d3 * (d3 + 2 * r);
    double y13 = l - (l - y3) / d3 * (d3 + 2 * r);

    double d1 = sqrt(sqr(x13 - x1) + sqr(y13 - y1));
    double x01 = x13 - (x13 - x1) / d1 * (d1 + 2 * r);
    double y01 = y13 - (y13 - y1) / d1 * (d1 + 2 * r);

    double angle02 = atan2(y02 - y01, x02 - x01);
    double angle13 = atan2(y13 - y1, x13 - x1);
    double angle01 = 2 * (angle13 + PI / 2) - angle02;
    if (angle01 >= PI) angle01 -= 2 * PI;
    if (angle01 <= -PI) angle01 += 2 * PI;

    double x0 = x01 - (y01 - h) / tan(angle01);
    double y0 = h;

    double dot01 = (x01 - x0) * (x13 - x1) + (y01 - y0) * (y13 - y1);
    double dot02 = (x02 - x01) * (0 - x2) + (y02 - y01) * (l - y2);
    double dot13 = (x13 - x1) * (w - x3) + (y13 - y1) * (l - y3);

    if (
        x0 > r && x0 < w - r && angle01 > 0
        && dot01 > 0 && dot02 > 0 && dot13 > 0
        && !collide(x0, y0, x01, y01, x2, y2, r)
        // && !collide(x0, y0, x01, y01, x3, y3, r)
        // && !collide(x1, y1, x13, y13, x2, y2, r)
        // && !collide(x01, y01, x02, y02, x3, y3, r)
    ) {
        printf("%.2f %.2f\n", x0, angle01 * 180 / PI);
    } else {
        printf("impossible\n");
    }

    return 0;
}
