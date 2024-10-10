// https://open.kattis.com/problems/platformplacing

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int x[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, s, k;
    cin >> n >> s >> k;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        x[i] *= 2;
    }

    int tot = 0;
    int prev = -2e5;
    int r = 0;

    x[n] = 2e9 + 2e5;
    sort(x, x + n);

    for (int i = 0; i <= n; ++i) {
        if (x[i] - prev < 2 * s) {
            cout << -1 << endl;

            return 0;
        }

        int r_new = max(min(x[i] - prev - r, k), s);

        if (x[i] - prev - r >= k) {
            tot += r;
        } else {
            tot += x[i] - prev - r_new;
        }

        r = r_new;
        prev = x[i];
    }

    cout << tot << endl;

    return 0;
}
