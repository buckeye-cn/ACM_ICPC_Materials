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

        int n;
        cin >> n;

        int x[n];
        int y[n];

        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }

        long double pos = 1e-10l;
        int tot = 1;

        while (pos < 1) {
            while (true) {
                bool found = false;

                for (int j = 0; j < n - 1; ++j) {
                    if ((x[j] - x[j + 1]) * pos + (y[j] - y[j + 1]) * (1 - pos) > 0) {
                        swap(x[j], x[j + 1]);
                        swap(y[j], y[j + 1]);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    break;
                }
            }

            long double l = pos;
            long double r = 1;

            while (r - l > 4e-19l) {
                long double m = (l + r) / 2;
                bool found = false;

                for (int j = 0; j < n - 1; ++j) {
                    if ((x[j] - x[j + 1]) * m + (y[j] - y[j + 1]) * (1 - m) > 0) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    r = m;
                } else {
                    l = m;
                }
            }

            if (r < 1) {
                tot += 1;
            }
            // cerr << l << ' ' << r << ' ' << pos << endl;

            pos = r;
        }

        cout << tot << endl;
    }

    return 0;
}
