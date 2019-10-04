// https://open.kattis.com/problems/pizzacutting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

int r, dx, dy, x, y, sqr_r;
double p;

int test(int delta, double x1, double x2, double y1, double y2) {
    int count = 0;
    double dxx = 1. / 1024 * dx * delta;
    double dyy = 1. / 1024 * dy * delta;

    for (double xx = x1 + 0.5 * dxx; xx < x2; xx += dxx) {
        for (double yy = y1 + 0.5 * dyy; yy < y2; yy += dyy) {
            count += sqr(xx) + sqr(yy) < sqr_r;
        }
    }

    return delta * delta * count;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> r >> dx >> dy >> x >> y >> p;

    sqr_r = r * r;

    while (x + dx <= -r) x += dx;
    while (x > -r) x -= dx;
    while (y + dy <= -r) y += dy;
    while (y > -r) y -= dy;

    vector<int> all;
    int best = 0;

    for (int i = 0; x + dx * i < r && !best; ++i) {
        double x1 = x + dx * i;
        double x2 = x + dx * i + dx;

        for (int j = 0; y + dy * j < r && !best; ++j) {
            double y1 = y + dy * j;
            double y2 = y + dy * j + dy;

            if (
                sqr(x1) + sqr(y1) <= sqr_r
                && sqr(x1) + sqr(y2) <= sqr_r
                && sqr(x2) + sqr(y1) <= sqr_r
                && sqr(x2) + sqr(y2) <= sqr_r
            ) {
                best = 1048576;
            }
        }
    }

    for (int i = 0; x + dx * i < r; ++i) {
        double x1 = x + dx * i;
        double x2 = x + dx * i + dx;

        for (int j = 0; y + dy * j < r; ++j) {
            double y1 = y + dy * j;
            double y2 = y + dy * j + dy;

            if (
                sqr(x1) + sqr(y1) <= sqr_r
                && sqr(x1) + sqr(y2) <= sqr_r
                && sqr(x2) + sqr(y1) <= sqr_r
                && sqr(x2) + sqr(y2) <= sqr_r
            ) {
                continue;
            }

            if (
                ((x1 >= 0) == (x2 >= 0))
                && ((y1 >= 0) == (y2 >= 0))
                && sqr(x1) + sqr(y1) >= sqr_r
                && sqr(x1) + sqr(y2) >= sqr_r
                && sqr(x2) + sqr(y1) >= sqr_r
                && sqr(x2) + sqr(y2) >= sqr_r
            ) {
                continue;
            }

            int count;

            for (int delta = 64; delta >= 1; delta /= 2) {
                count = test(delta, x1, x2, y1, y2);

                if (count + 2 * delta * delta < p * best || count - 2 * delta * delta > p * 1048576) {
                    break;
                }
            }

            if (best < count) {
                best = test(1, x1, x2, y1, y2);
            }

            all.push_back(count);
        }
    }

    int total = 0;

    for (int i: all) {
        total += i < p * best;
    }

    cout << total << endl;

    return 0;
}
