// https://open.kattis.com/problems/freeweights

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int w[2][1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> w[i][j];
        }
    }

    int lo = 0;
    int hi = 1e9 + 1;

    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;

        bool ok = true;

        for (int i = 0; i < 2; ++i) {
            int last = 0;

            for (int j = 0; j < n; ++j) {
                if (w[i][j] >= mid) {
                    if (last) {
                        ok &= last == w[i][j];
                        last = 0;
                    } else {
                        last = w[i][j];
                    }
                }
            }

            ok &= !last;
        }

        if (ok) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << lo << endl;

    return 0;
}
