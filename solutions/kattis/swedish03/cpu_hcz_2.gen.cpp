// https://open.kattis.com/problems/cpu
// code generator

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
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
    if (x == 2) return true;

    for (int iter = 0; iter < 5; ++iter) {
        if (witness(rand() % (x - 2) + 1, x)) {
            return false;
        }
    }

    return true;
}

long limit = 1e5;
long xlimit = 1e15;

set<long> result;

void test(long a, long b) {
    long v = 1;
    long p = 1;

    for (long i = 1; true; ++i) {
        p = p * a + b;

        if (!prime(p)) break;
        if (v > xlimit / p) break;

        v = v * p;

        if (i >= 3) {
            result.insert(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (long a = 1; a < limit; ++a) {
        for (long b = 2 - a; a * (a + b - 1) < limit; ++b) {
            test(a, b);
        }
    }

    long last = 0;

    for (long i: result) {
        printf("%ld,", i);
        last = i;
    }

    return 0;
}
