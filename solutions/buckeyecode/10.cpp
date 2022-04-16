#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

double xi[200];
double yi[200];
double ri[200];
double ai[200];
double vi[200];
double vix[200];
double viy[200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double x, y, r, a, v, d, vx, vy;
    cin >> x >> y >> r >> a >> v >> d;

    vx = cos(a / 180 * PI) * v;
    vy = sin(a / 180 * PI) * v;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> xi[i] >> yi[i] >> ri[i] >> ai[i] >> vi[i];

        xi[i] -= x;
        yi[i] -= y;
        ri[i] += r;
        vix[i] = cos(ai[i] / 180 * PI) * vi[i] - vx;
        viy[i] = sin(ai[i] / 180 * PI) * vi[i] - vy;
    }

    for (double t = 0; t < d / v; t += 1e-5 * d / v) {
        for (int i = 0; i < n; ++i) {
            double xxi = xi[i] + vix[i] * t;
            double yyi = yi[i] + viy[i] * t;

            if (sqr(xxi) + sqr(yyi) < sqr(ri[i])) {
                cout << round(t * 100) / 100 << endl;

                return 0;
            }
        }
    }

    cout << "safe" << endl;

    return 0;
}
