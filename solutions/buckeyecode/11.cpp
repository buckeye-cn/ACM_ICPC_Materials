#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// Miller-Rabin
bool witness(long base, long x) {
    long u = x - 1;
    int r = 0;

    for (; !(u & 1); u >>= 1){
        r += 1;
    }

    long v = base % x;

    while (u >>= 1) {
        base = __int128(base) * base % x;

        if (u & 1) {
            v = __int128(v) * base % x;
        }
    }

    if (v == 1 || v == x - 1) return false;

    for (int i = 1; i < r; ++i) {
        v = __int128(v) * v % x;

        if (v == x - 1) return false;
    }

    return true;
}

bool prime(long x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    if (!(x & 1)) return false;

    for (int iter = 0; iter < 5; ++iter) {
        if (witness(hash<string>()(string {iter}) % (x - 2) + 1, x)) {
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int s, l;
    string data;
    cin >> s >> l >> data;

    long result = 0;

    for (int i = l; i >= 1 && !result; --i) {
        for (int j = 0; j + i <= s; ++j) {
            if (data[j] > '0') {
                long v = 0;

                for (int k = j; k < j + i; ++k) {
                    v *= 10;
                    v += data[k] - '0';
                }

                // cerr << v << endl;

                if (v > 1 && prime(v)) {
                    result = max(result, v);
                }
            }
        }
    }

    if (result) {
        cout << result << endl;
    } else {
        cout << "No Primes" << endl;
    }

    return 0;
}
