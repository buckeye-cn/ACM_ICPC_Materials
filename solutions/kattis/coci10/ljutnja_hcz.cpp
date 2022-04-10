// https://open.kattis.com/problems/ljutnja

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long v[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    long base = 0;

    for (long i = 1 << 30; i >= 1; i >>= 1) {
        long s = 0;

        for (int j = 0; j < n; ++j) {
            s += v[j] - min(v[j], base + i);
        }

        if (m >= s) {
            m -= s;

            for (int j = 0; j < n; ++j) {
                v[j] = min(v[j], base + i);
            }
        } else {
            base += i;
        }
    }

    long total = 0;

    for (int i = 0; i < n; ++i) {
        if (m && v[i] == base + 1) {
            m -= 1;
            v[i] -= 1;
        }

        total += v[i] * v[i];
    }

    cout << total << endl;

    return 0;
}
