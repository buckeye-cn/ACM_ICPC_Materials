// https://open.kattis.com/problems/skysthelimit

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double h[100002];
int hull[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    double k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];

        h[i] -= k * i * (n + 1 - i);
    }

    int hull_n = 1;

    for (int i = 1; i <= n + 1; ++i) {
        while (hull_n >= 2) {
            int dx = hull[hull_n - 1] - hull[hull_n - 2];
            int dxx = i - hull[hull_n - 2];
            double dy = h[hull[hull_n - 1]] - h[hull[hull_n - 2]];
            double dyy = h[i] - h[hull[hull_n - 2]];

            if (dyy * dx < dy * dxx) {
                break;
            }

            hull_n -= 1;
        }

        hull[hull_n++] = i;
    }

    for (int i = 1; i < hull_n; ++i) {
        int l = hull[i - 1];
        int r = hull[i];

        for (int j = l; j < r; ++j) {
            h[j] = (h[l] * (r - j) + h[r] * (j - l)) / (r - l);
        }
    }

    double max_h = 0;

    for (int i = 1; i <= n; ++i) {
        h[i] += k * i * (n + 1 - i);
        max_h = max(max_h, h[i]);
    }

    cout << max_h << endl;

    return 0;
}
