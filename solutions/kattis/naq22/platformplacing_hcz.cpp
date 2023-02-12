// https://open.kattis.com/problems/platformplacing

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, s, k;
    cin >> n >> s >> k;

    set<int> xs;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        xs.insert(x * 2);
    }

    int tot = 0;
    int prev = -2e5;
    int r = 0;

    xs.insert(2e9 + 2e5);

    for (int x: xs) {
        if (x - prev < 2 * s) {
            cout << -1 << endl;

            return 0;
        }

        int r_new = max(min(x - prev - r, k), s);

        if (x - prev - r >= k) {
            tot += r;
        } else {
            tot += x - prev - r_new;
        }

        r = r_new;
        prev = x;
    }

    cout << tot << endl;

    return 0;
}
