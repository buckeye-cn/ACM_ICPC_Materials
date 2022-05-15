#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int from[20000];
int to[20000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int np = 0;
    int vfrom = 1;
    int vto = 0;

    for (int i = 1; i < 5000; ++i) {
        for (int j = 0; j < 4; ++j) {
            from[np] = vfrom;
            to[np] = vto;
            np += 1;
            vfrom += 2 * i;
            vto += 2 * i - 2;
        }
        vfrom += 1;
        vto += 1;
    }

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n, k;
        cin >> n >> k;

        if (k < n - 1 || k % 2) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        int last = n * n - 1;
        int limit = n * n - 1 - k;
        int nc = 0;

        for (int i = np - 1; i >= 1; --i) {
            if (from[i] <= last && limit >= from[i] - to[i] - 1) {
                last = to[i];
                limit -= from[i] - to[i] - 1;
                nc += 1;
            }
        }

        cout << nc << endl;

        last = n * n - 1;
        limit = n * n - 1 - k;

        for (int i = np - 1; i >= 1; --i) {
            if (from[i] <= last && limit >= from[i] - to[i] - 1) {
                last = to[i];
                limit -= from[i] - to[i] - 1;
                cout << n * n - from[i] << ' ' << n * n - to[i] << endl;
                nc += 1;
            }
        }
    }

    return 0;
}
