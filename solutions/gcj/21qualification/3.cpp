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

        int n, tot;
        cin >> n >> tot;

        int l[n];
        for (int i = 0; i < n; ++i) {
            l[i] = i + 1;
        }

        for (int i = n - 2; i >= 0; --i) {
            int j_min = max(i, min(tot - 1, n - 1));

            tot -= j_min - i + 1;

            for (int j = 0; i + j < j_min - j; ++j) {
                int t = l[i + j];

                l[i + j] = l[j_min - j];
                l[j_min - j] = t;
            }
        }

        if (tot) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (int i = 0; i < n; ++i) {
                cout << l[i];

                if (i < n - 1) {
                    cout << ' ';
                } else {
                    cout << endl;
                }
            }
        }
    }

    return 0;
}
