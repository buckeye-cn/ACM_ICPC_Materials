// https://open.kattis.com/problems/threedprinter

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double v_all = 0;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int f;
        cin >> f;

        double x00, y00, z00;

        for (int j = 0; j < f; ++j) {
            int v;
            cin >> v;

            double x0, y0, z0, xp, yp, zp;

            for (int k = 0; k < v; ++k) {
                double x, y, z;
                cin >> x >> y >> z;

                if (!k) {
                    x0 = x;
                    y0 = y;
                    z0 = z;

                    if (!j) {
                        x00 = x;
                        y00 = y;
                        z00 = z;
                    }
                } else {
                    double xx = (yp - y0) * (z - z0)
                        - (zp - z0) * (y - y0);
                    double yy = (zp - z0) * (x - x0)
                        - (xp - x0) * (z - z0);
                    double zz = (xp - x0) * (y - y0)
                        - (yp - y0) * (x - x0);

                    v_all += abs(
                        (x0 - x00) * xx
                        + (y0 - y00) * yy
                        + (z0 - z00) * zz
                    ) / 6;
                }

                xp = x;
                yp = y;
                zp = z;
            }
        }
    }

    printf("%.2f\n", v_all);

    return 0;
}
