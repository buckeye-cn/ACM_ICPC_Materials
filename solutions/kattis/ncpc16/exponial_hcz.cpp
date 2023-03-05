// https://open.kattis.com/problems/exponial

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long solve(long n, long m) {
    if (m == 1) {
        return 0;
    }

    if (n == 1) {
        return 1 % m;
    }

    if (n == 2) {
        return 2 % m;
    }

    if (n == 3) {
        return 9 % m;
    }

    if (n == 4) {
        return 262144 % m;
    }

    // Euler's totient function
    long mm = m;
    long e = m;

    for (long i = 2; i * i <= mm; ++i) {
        if (mm % i == 0) {
            e /= i;
            e *= i - 1;

            while (mm % i == 0) {
                mm /= i;
            }
        }
    }

    if (mm > 1) {
        e /= mm;
        e *= mm - 1;
    }

    long res = 1;
    long nn = n;

    for (long i = solve(n - 1, e) + e; i; i >>= 1) {
        if (i & 1) {
            res *= nn;
            res %= m;
        }

        nn *= nn;
        nn %= m;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n, m;
    cin >> n >> m;

    cout << solve(n, m) << endl;

    return 0;
}
