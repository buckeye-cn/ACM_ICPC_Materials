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

    int t;
    cin >> t;

    double ss = PI / 4 / 3e-7;

    for (int n_case = 1; n_case <= t; ++n_case) {
        double f, rr, tt, r, g;
        cin >> f >> rr >> tt >> r >> g;

        tt += f;
        rr -= tt;
        g += 2 * r;
        r += f;
        tt /= rr;
        r /= rr;
        g /= rr;

        if (r / g < 1e-5) {
            cout << "Case #" << n_case << ": " << 1 - sqr(1 - r / g) / sqr(1 + tt) << endl;
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

        cout << "Case #" << n_case << ": " << 1 - s / ss / sqr(1 + tt) << endl;
    }

    return 0;
}
