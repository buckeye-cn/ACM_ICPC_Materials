// https://open.kattis.com/problems/tractor

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
    cout.precision(15);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long x, y;
        cin >> x >> y;
        x += 1;
        y += 1;

        long tot = 0;

        for (int j = 0; j < 32; ++j) {
            long mask = (1l << j) - 1;
            long xx = min(x, 1l << j);
            long yy = min(y, 1l << j);

            for (int kx = 0; kx < 32; ++kx) {
                if (xx & (1l << kx)) {
                    long mask_x = (1l << kx) - 1;
                    long x_up = xx & ~mask_x;
                    long x_lo = x_up ^ (1l << kx);

                    for (int ky = 0; ky < 32; ++ky) {
                        if (yy & (1l << ky)) {
                            long mask_y = (1l << ky) - 1;
                            long y_up = yy & ~mask_y;
                            long y_lo = y_up ^ (1l << ky);

                            long f = (x_lo ^ y_lo) | mask_x | mask_y;

                            if ((f & mask) == mask) {
                                tot += 1l << min(min(kx, ky), j);
                            }
                        }
                    }
                }
            }
        }

        cout << tot << endl;
    }

    return 0;
}
