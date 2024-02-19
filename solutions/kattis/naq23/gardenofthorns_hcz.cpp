// https://open.kattis.com/problems/gardenofthorns

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

    int n;
    double r, w, h;
    cin >> n >> r >> w >> h;

    double result = 0;

    for (int i = 0; i < n; ++i) {
        double x, y, v;
        cin >> x >> y >> v;

        if (sqr(x) + sqr(y) <= sqr(r)) {
            result += v * x * y;
        } else {
            result += v * sqr(r) * PI / 4;

            if (x < r) result += v * x * sqrt(sqr(r) - sqr(x)) / 2 - v * sqr(r) * acos(x / r) / 2;
            if (y < r) result += v * y * sqrt(sqr(r) - sqr(y)) / 2 - v * sqr(r) * acos(y / r) / 2;
        }

        if (sqr(w - x) + sqr(y) <= sqr(r)) {
            result += v * (w - x) * y;
        } else {
            result += v * sqr(r) * PI / 4;

            if (w - x < r) result += v * (w - x) * sqrt(sqr(r) - sqr(w - x)) / 2 - v * sqr(r) * acos((w - x) / r) / 2;
            if (y < r) result += v * y * sqrt(sqr(r) - sqr(y)) / 2 - v * sqr(r) * acos(y / r) / 2;
        }

        if (sqr(x) + sqr(h - y) <= sqr(r)) {
            result += v * x * (h - y);
        } else {
            result += v * sqr(r) * PI / 4;

            if (x < r) result += v * x * sqrt(sqr(r) - sqr(x)) / 2 - v * sqr(r) * acos(x / r) / 2;
            if (h - y < r) result += v * (h - y) * sqrt(sqr(r) - sqr(h - y)) / 2 - v * sqr(r) * acos((h - y) / r) / 2;
        }

        if (sqr(w - x) + sqr(h - y) <= sqr(r)) {
            result += v * (w - x) * (h - y);
        } else {
            result += v * sqr(r) * PI / 4;

            if (w - x < r) result += v * (w - x) * sqrt(sqr(r) - sqr(w - x)) / 2 - v * sqr(r) * acos((w - x) / r) / 2;
            if (h - y < r) result += v * (h - y) * sqrt(sqr(r) - sqr(h - y)) / 2 - v * sqr(r) * acos((h - y) / r) / 2;
        }
    }

    cout << result / w / h << endl;

    return 0;
}
