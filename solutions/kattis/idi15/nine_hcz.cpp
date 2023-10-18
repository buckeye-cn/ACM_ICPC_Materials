// https://open.kattis.com/problems/nine

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

long p9[63];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    p9[0] = 9;

    for (long i = 1; i < 63; ++i) {
        p9[i] = p9[i - 1] * p9[i - 1] % MOD;
    }

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        long d;
        cin >> d;

        long v = 8;

        for (long j = 0; j < 63; ++j) {
            if ((d - 1) & (1l << j)) {
                v *= p9[j];
                v %= MOD;
            }
        }

        cout << v << endl;
    }

    return 0;
}
