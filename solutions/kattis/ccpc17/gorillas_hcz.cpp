// https://open.kattis.com/problems/gorillas

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double x[1000];
double y[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        double xs, ys, xt, yt;
        cin >> xs >> ys >> xt >> yt;

        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            cin >> x[j] >> y[j];
        }

        double l = max(ys, yt);
        double r = 1e8;

        while (r - l > 1e-5) {
            double m = (l + r) / 2;

            double v1 = -sqrt(m - ys);
            double v2 = sqrt(m - yt);
            double k = (v1 - v2) / (xs - xt);
            double c = k * xs - v1;

            bool ok = true;

            for (int j = 0; j < n; ++j) {
                ok &= m - sqr(k * x[j] - c) > y[j];
            }

            if (ok) {
                r = m;
            } else {
                l = m;
            }
        }

        cout << r << endl;
    }

    return 0;
}
