// https://open.kattis.com/problems/kingscolors

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

long kci[2501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n, k;
    cin >> n >> k;

    for (int i = 0; i <= k; ++i) {
        kci[i] = 1;

        for (int j = i - 1; j >= 1; --j) {
            kci[j] += kci[j - 1];

            if (i % 32 == k % 32) {
                kci[j] %= MOD;
            }
        }
    }

    long result = 0;

    for (int i = 2; i <= k; ++i) {
        long p = kci[i] * i % MOD;
        long pp = i - 1;

        for (int j = 0; j < 12; ++j) {
            if ((1 << j) & (n - 1)) {
                p = p * pp % MOD;
            }

            pp = pp * pp % MOD;
        }

        result = p - result;
    }

    cout << (result % MOD + MOD) % MOD << endl;

    return 0;
}
