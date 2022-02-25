// https://open.kattis.com/problems/avoidingasteroids

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double sx, sy, sz, bx, by, bz;
    cin >> sx >> sy >> sz >> bx >> by >> bz;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        double px, py, pz, dx, dy, dz, r2;
        cin >> px >> py >> pz >> dx >> dy >> dz;

        int m;
        cin >> m;

        r2 = 0;

        for (int j = 0; j < m; ++j) {
            double cx, cy, cz;
            cin >> cx >> cy >> cz;

            r2 = max(r2, sqr(cx - px) + sqr(cy - py) + sqr(cz - pz));
        }

        double dll, dlr, drl, drr;

        double ll = 0;
        double rr = 6e6;

        while (rr - ll > 1e-3) {
            double xx = px + ll * dx;
            double yy = py + ll * dy;
            double zz = pz + ll * dz;
            double l = 0;
            double r = 1;

            while (r - l > 1e-9) {
                double x = (1 - l) * sx + l * bx;
                double y = (1 - l) * sy + l * by;
                double z = (1 - l) * sz + l * bz;

                dll = sqr(x - xx) + sqr(y - yy) + sqr(z - zz);

                x = (1 - r) * sx + r * bx;
                y = (1 - r) * sy + r * by;
                z = (1 - r) * sz + r * bz;

                dlr = sqr(x - xx) + sqr(y - yy) + sqr(z - zz);

                if (dll < dlr) {
                    r = (l + r) / 2;
                } else {
                    l = (l + r) / 2;
                }
            }

            xx = px + rr * dx;
            yy = py + rr * dy;
            zz = pz + rr * dz;
            l = 0;
            r = 1;

            while (r - l > 1e-9) {
                double x = (1 - l) * sx + l * bx;
                double y = (1 - l) * sy + l * by;
                double z = (1 - l) * sz + l * bz;

                drl = sqr(x - xx) + sqr(y - yy) + sqr(z - zz);

                x = (1 - r) * sx + r * bx;
                y = (1 - r) * sy + r * by;
                z = (1 - r) * sz + r * bz;

                drr = sqr(x - xx) + sqr(y - yy) + sqr(z - zz);

                if (drl < drr) {
                    r = (l + r) / 2;
                } else {
                    l = (l + r) / 2;
                }
            }

            if (dll < drl) {
                rr = (ll + rr) / 2;
            } else {
                ll = (ll + rr) / 2;
            }
        }

        if (dll < r2) {
            cout << "Surrender" << endl;

            return 0;
        }
    }

    cout << "Go" << endl;

    return 0;
}
