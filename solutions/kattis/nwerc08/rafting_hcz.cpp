// https://open.kattis.com/problems/rafting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double distance(
    double x, double y,
    double x1, double y1, double x2, double y2
) {
    double projection = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1))
        / (sqr(x2 - x1) + sqr(y2 - y1));

    if (projection < 0) projection = 0;
    if (projection > 1) projection = 1;

    double vx = x1 + (x2 - x1) * projection;
    double vy = y1 + (y2 - y1) * projection;

    return sqrt(sqr(x - vx) + sqr(y - vy));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    while (t--) {
        int n[2];
        int x[2][100];
        int y[2][100];

        for (int i = 0; i < 2; ++i) {
            cin >> n[i];

            for (int j = 0; j < n[i]; ++j) {
                cin >> x[i][j] >> y[i][j];
            }
        }

        double best = 1000;

        for (int i = 0; i < n[0]; ++i) {
            for (int j = 0; j < n[1]; ++j) {
                best = min(best, distance(x[0][i], y[0][i], x[1][j], y[1][j], x[1][(j + 1) % n[1]], y[1][(j + 1) % n[1]]) / 2);
            }
        }

        cout << best << endl;
    }

    return 0;
}
