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

        long x[n];
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }

        int tot = 0;

        for (int i = 1; i < n; ++i) {
            if (x[i - 1] > 1e12l) {
                x[i - 1] /= 10;
                tot += n - i;
            }

            long x1 = x[i - 1] + 1;
            int t1 = 0;

            while (x1 > x[i]) {
                x1 /= 10;
                t1 += 1;
            }

            long x2 = x[i];
            int t2 = 0;

            while (x2 <= x[i - 1]) {
                x2 *= 10;
                t2 += 1;
            }

            if (t1 < t2) {
                tot += t1;
                x[i] = x[i - 1] + 1;
            } else {
                tot += t2;
                x[i] = x2;
            }

            // cerr << x[i] << ' ';
        }

        cout << tot << endl;
    }

    return 0;
}
