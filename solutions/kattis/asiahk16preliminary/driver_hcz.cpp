// https://open.kattis.com/problems/driver

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
long c[100000];
long t[100000];
long tot;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    long now = 0;
    long best = 1 << 30;

    for (int i = 0; i < n - 1; ++i) {
        now += 1;
        if (best > c[i]) {
            best = c[i];
        }

        tot += c[i];
        if (now < t[i + 1]) {
            long k = (t[i + 1] - now + 1) & ~1;
            now += k;
            tot += k * best;
        }
    }

    cout << tot << endl;

    return 0;
}
