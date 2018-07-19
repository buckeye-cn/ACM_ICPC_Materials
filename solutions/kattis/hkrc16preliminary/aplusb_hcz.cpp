// https://open.kattis.com/problems/aplusb

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
long _slot[102400];
long *slot = _slot + 51200;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;

        ++slot[a];
    }

    long tot = 0;

    // 0 0

    tot += slot[0] * (slot[0] - 1) * (slot[0] - 2);

    // 0 j

    for (int j = -50000; j <= -1; ++j) {
        tot += 2 * slot[0] * slot[j] * (slot[j] - 1);
    }
    for (int j = 1; j <= 50000; ++j) {
        tot += 2 * slot[0] * slot[j] * (slot[j] - 1);
    }

    // i i

    for (int i = -25000; i <= -1; ++i) {
        tot += slot[i] * (slot[i] - 1) * slot[i + i];
    }
    for (int i = 1; i <= 25000; ++i) {
        tot += slot[i] * (slot[i] - 1) * slot[i + i];
    }

    // i j

    for (int i = -25000; i <= -1; ++i) {
        for (int j = -50000 - i; j <= i - 1; ++j) {
            tot += 2 * slot[i] * slot[j] * slot[i + j];
        }
    }
    for (int i = 1; i <= 25000; ++i) {
        for (int j = i + 1; j <= 50000 - i; ++j) {
            tot += 2 * slot[i] * slot[j] * slot[i + j];
        }
    }
    for (int i = -50000; i <= -1; ++i) {
        for (int j = 1; j <= 50000; ++j) {
            tot += 2 * slot[i] * slot[j] * slot[i + j];
        }
    }

    cout << tot << endl;

    return 0;
}
