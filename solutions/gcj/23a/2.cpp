#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int pos[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int m, r, n;
        cin >> m >> r >> n;

        bool ok = true;
        int nn = 1;
        pos[0] = -r;

        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;

            if (nn >= 2 && pos[nn - 2] + r >= x - r) {
                pos[nn - 1] = x;
            } else if (pos[nn - 1] + r >= x - r) {
                pos[nn] = x;
                nn += 1;
            } else {
                ok = false;
            }
        }

        if (nn >= 2 && pos[nn - 2] + r >= m) {
            // nothing
        } else if (pos[nn - 1] + r >= m) {
            nn += 1;
        } else {
            ok = false;
        }

        if (ok) {
            cout << nn - 2 << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
