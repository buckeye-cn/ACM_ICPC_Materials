// https://open.kattis.com/problems/curvyblocks

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

    double b0, b1, b2, b3, t0, t1, t2, t3;
    while (cin >> b0 >> b1 >> b2 >> b3 >> t0 >> t1 >> t2 >> t3) {
        double k0 = t0 - b0;
        double k1 = t1 - b1;
        double k2 = t2 - b2;
        double k3 = t3 - b3;

        double lo = min(k0, k0 + k1 + k2 + k3);
        double hi = max(k0, k0 + k1 + k2 + k3);

        double delta = 4 * k2 * k2 - 12 * k1 * k3;
        if (delta >= 0) {
            double x1 = (-2 * k2 - sqrt(delta)) / (6 * k3);
            double x2 = (-2 * k2 + sqrt(delta)) / (6 * k3);

            if (0 < x1 && x1 < 1) {
                lo = min(lo, k0 + k1 * x1 + k2 * x1 * x1 + k3 * x1 * x1 * x1);
                hi = max(hi, k0 + k1 * x1 + k2 * x1 * x1 + k3 * x1 * x1 * x1);
            }
            if (0 < x2 && x2 < 1) {
                lo = min(lo, k0 + k1 * x2 + k2 * x2 * x2 + k3 * x2 * x2 * x2);
                hi = max(hi, k0 + k1 * x2 + k2 * x2 * x2 + k3 * x2 * x2 * x2);
            }
        }

        cout << hi - lo << endl;
    }

    return 0;
}
