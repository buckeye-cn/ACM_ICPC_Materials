// https://open.kattis.com/problems/randommanhattan

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double x[200000];
double y[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int l = 0;
    int r = 0;
    int b = 0;
    int t = 0;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];

        x[i + n] = x[i];
        y[i + n] = y[i];

        if (x[l] > x[i]) l = i;
        if (x[r] < x[i]) r = i;
        if (y[b] > y[i]) b = i;
        if (y[t] < y[i]) t = i;
    }

    int pb = l + n;
    int pt = l;
    int pl = b;
    int pr = b + n;

    double eh = 0;
    double ew = 0;
    double hsum = 0;
    double wsum = 0;
    double hksum = 0;
    double wksum = 0;

    for (int i = 0; i < 200000; ++i) {
        double xx = (0.9999975 - 0.000005 * i) * x[l] + (0.0000025 + 0.000005 * i) * x[r];
        double yy = (0.9999975 - 0.000005 * i) * y[b] + (0.0000025 + 0.000005 * i) * y[t];

        while (xx > x[pb - 1]) pb -= 1;
        while (xx > x[pt + 1]) pt += 1;
        while (yy > y[pl + 1]) pl += 1;
        while (yy > y[pr - 1]) pr -= 1;

        double yb = ((x[pb - 1] - xx) * y[pb] + (xx - x[pb]) * y[pb - 1]) / (x[pb - 1] - x[pb]);
        double yt = ((x[pt + 1] - xx) * y[pt] + (xx - x[pt]) * y[pt + 1]) / (x[pt + 1] - x[pt]);
        double xl = ((y[pl + 1] - yy) * x[pl] + (yy - y[pl]) * x[pl + 1]) / (y[pl + 1] - y[pl]);
        double xr = ((y[pr - 1] - yy) * x[pr] + (yy - y[pr]) * x[pr - 1]) / (y[pr - 1] - y[pr]);
        double h = yt - yb;
        double w = xr - xl;

        eh += 2 * h * (i * hsum - hksum);
        ew += 2 * w * (i * wsum - wksum);
        hsum += h;
        wsum += w;
        hksum += h * i;
        wksum += w * i;

        // if (i % 10000 == 0) {
        //     cerr << xx << '\t' << yb << ".." << yt << endl;
        //     cerr << xl << ".." << xr << '\t' << yy << endl;
        // }
    }

    cout << eh / (hsum * hsum) * (x[r] - x[l]) / 200000 + ew / (wsum * wsum) * (y[t] - y[b]) / 200000 << endl;

    return 0;
}
