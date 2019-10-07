// https://open.kattis.com/problems/yikes

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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        double m, b, d, t;
        cin >> m >> b >> d >> t;

        // tt * m - t * m == y + 5.5
        // tt * b == x + d + 4 * j

        int cross = 10;
        int collision = 0;

        for (double y = -0.5; y <= 0.5 && !collision; y += 0.001) {
            double tt = (y + 5.5) / m + t;

            double xm2 = sqrt(0.25 - y * y);
            double xm1 = -xm2;
            double xb = tt * b - d;

            if (xm1 > xb) cross = 0;

            for (int j = 0; j < 10 && !collision; ++j) {
                double xb2 = xb - 4 * j;
                double xb1 = xb2 - 2;
                double xb0 = xb1 - 2;

                if (xm1 <= xb2 && xm2 >= xb1) {
                    collision = j + 1;
                }
                if (xm2 < xb1 && xm1 > xb0) {
                    cross = j + 1;
                }
            }
        }

        if (collision) {
            cout << "Collision with bicycle " << collision << endl;
        } else if (cross) {
            cout << "Max crosses safely after bicycle " << cross << endl;
        } else {
            cout << "Max beats the first bicycle" << endl;
        }
    }

    return 0;
}
