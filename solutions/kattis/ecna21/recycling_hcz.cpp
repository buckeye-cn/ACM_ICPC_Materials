// https://open.kattis.com/problems/recycling

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long est[100002];
int l[100000];
long h[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> est[i];
    }

    int t = 0;
    long best = -1;
    int best_l = -1;
    int best_r = -1;

    for (int i = 1; i <= n + 1; ++i) {
        int p = i;

        while (t && h[t - 1] >= est[i]) {
            t -= 1;
            p = l[t];

            long vol = (i - l[t]) * h[t];

            if (best < vol || (best == vol && best_l > l[t])) {
                best = vol;
                best_l = l[t];
                best_r = i - 1;
            }
        }

        if (!t || h[t - 1] < est[i]) {
            h[t] = est[i];
            l[t] = p;
            t += 1;
        }
    }

    cout << best_l << ' ' << best_r << ' ' << best << endl;

    return 0;
}
