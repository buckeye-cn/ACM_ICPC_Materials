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

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int c = 1e6;
        int m = 1e6;
        int y = 1e6;
        int k = 1e6;

        for (int i = 0; i < 3; ++i) {
            int cc, mm, yy, kk;
            cin >> cc >> mm >> yy >> kk;

            c = min(c, cc);
            m = min(m, mm);
            y = min(y, yy);
            k = min(k, kk);
        }

        if (c + m + y + k < 1e6) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            int remain = c + m + y + k - 1e6;
            int delta = min(c, remain);

            c -= delta;
            remain -= delta;
            delta = min(m, remain);
            m -= delta;
            remain -= delta;
            delta = min(y, remain);
            y -= delta;
            remain -= delta;
            k -= remain;

            cout << c << ' ' << m << ' ' << y << ' ' << k << endl;
        }
    }

    return 0;
}
