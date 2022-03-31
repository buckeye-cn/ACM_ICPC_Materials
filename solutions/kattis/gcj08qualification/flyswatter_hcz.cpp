// https://open.kattis.com/problems/flyswatter

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
    cin >> n;

    double ss = PI / 4 / 3e-7;

    for (int i = 1; i <= n; ++i) {
        double f, rr, t, r, g;
        cin >> f >> rr >> t >> r >> g;

        t += f;
        rr -= t;
        g += 2 * r;
        r += f;
        t /= rr;
        r /= rr;
        g /= rr;

        if (r / g < 1e-5) {
            cout << "Case #" << i << ": " << 1 - sqr(1 - r / g) / sqr(1 + t) << endl;
            continue;
        }

        double gg = g - 2 * r;

        int dx = 0;
        int dy = 1 / g;
        double x = 0;
        double y = 1;
        double mx = 0;
        double my = 1 - dy * g;

        double s = 0;

        while (x < 1) {
            if (mx > r) {
                if (my < g - r) {
                    s += gg * dy + my - r;
                } else {
                    s += gg * (dy + 1);
                }
            }

            while (sqr(x) + sqr(y) > 1) {
                y -= 3e-7;
                my -= 3e-7;

                if (my < r) {
                    dy -= 1;
                    my += g;
                }
            }

            x += 3e-7;
            mx += 3e-7;

            if (mx > g - r) {
                dx += 1;
                mx -= g;
            }
        }

        cout << "Case #" << i << ": " << 1 - s / ss / sqr(1 + t) << endl;
    }

    return 0;
}
