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

    int t, n, m;
    cin >> t >> n >> m;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int tot[19];

        for (int i = 12; i <= 18; ++i) {
            for (int j = 0; j < 18; ++j) {
                if (j) cout << ' ';
                cout << i;
            }
            cout << endl;

            tot[i] = 0;
            for (int j = 0; j < 18; ++j) {
                int value;
                cin >> value;

                tot[i] += value;
            }
            tot[i] %= i;
        }

        // can be optimized
        for (int nn = 0; nn <= n; ++nn) {
            bool ok = true;

            for (int i = 12; i <= 18 && ok; ++i) {
                ok = (nn % i) == tot[i];
            }

            if (ok) {
                cout << nn << endl;
                break;
            }
        }

        int result;
        cin >> result;
    }

    return 0;
}
