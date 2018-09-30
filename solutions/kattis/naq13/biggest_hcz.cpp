// https://open.kattis.com/problems/biggest

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const double PI = acos(-1);

using namespace std;

bool cut[360 * 60 * 60 + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        long r, n, t1, t2, t3;
        cin >> r >> n >> t1 >> t2 >> t3;

        memset(cut, 0, sizeof(cut));

        long tt = 3600 * t1 + 60 * t2 + t3;

        for (long j = 0; !cut[tt * j % (360 * 60 * 60)] && j < n; ++j) {
            cut[tt * j % (360 * 60 * 60)] = true;
        }

        cut[360 * 60 * 60] = true;

        double best = 0;
        long last = 0;

        for (long j = 0; j <= 360 * 60 * 60; ++j) {
            if (cut[j]) {
                best = max(best, r * r * (j - last) / 360. / 60. / 60. * PI);
                last = j;
            }
        }

        printf("%.6f\n", best);
    }

    return 0;
}
