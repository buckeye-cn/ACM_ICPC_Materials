// https://open.kattis.com/problems/dinoscan

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int r, c1, c2;
long lmask[24];
long rmask[24];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> r >> c1 >> c2;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c1; ++j) {
            char c;
            cin >> c;

            if (c == '1') lmask[i] |= 1l << j;
        }
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c2; ++j) {
            char c;
            cin >> c;

            if (c == '1') rmask[i] |= 1l << j;
        }
    }

    long w = 0;
    long v = lmask[0] << 32 ^ rmask[0];

    while (v) {
        v ^= v & -v;
        ++w;
    }

    long mask = (1l << w) - 1;
    mask <<= 20;

    bool ok = true;

    for (int i = 0; i < r; ++i) {
        if (((lmask[i] << 20) ^ (rmask[i] << (20 + w - c2))) != mask) {
            ok = false;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}
