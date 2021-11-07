// https://open.kattis.com/problems/playingtheslots

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    double x[n];
    double y[n];

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }


    double best = INFINITY;

    for (double i = 0; i < PI; i += 1e-4) {
        double l = INFINITY;
        double r = -INFINITY;

        for (int j = 0; j < n; ++j) {
            double pos = x[j] * cos(i) + y[j] * sin(i);

            l = min(l, pos);
            r = max(r, pos);
        }

        best = min(best, r - l);
    }

    cout << best << endl;

    return 0;
}
