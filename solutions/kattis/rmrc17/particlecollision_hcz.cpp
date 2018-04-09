// https://open.kattis.com/problems/particlecollision

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

void norm(double &x, double &y) {
    double w = sqrt(sqr(x) + sqr(y));

    x /= w;
    y /= w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double x[3];
    double y[3];
    double vx, vy;
    double r;
    cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2] >> vx >> vy >> r;

    if (!vx && !vy) {
        cout << 5 << endl;

        return 0;
    }

    norm(vx, vy);

    int k = 0;

    for (int i = 0; i < 500000 && k < 10; ++i) {
        x[k] += 0.005 * vx;
        y[k] += 0.005 * vy;

        for (int j = 0; j < 3; ++j) {
            if (j != k) {
                if (sqr(x[j] - x[k]) + sqr(y[j] - y[k]) <= sqr(2 * r)) {
                    vx = x[j] - x[k];
                    vy = y[j] - y[k];
                    norm(vx, vy);
                    x[k] = NAN;
                    y[k] = NAN;

                    k = k * 10 + j;
                }
            }
        }
    }

    if (k == 0) cout << 5 << endl;
    if (k == 1) cout << 3 << endl;
    if (k == 2) cout << 4 << endl;
    if (k == 12) cout << 1 << endl;
    if (k == 21) cout << 2 << endl;

    return 0;
}
