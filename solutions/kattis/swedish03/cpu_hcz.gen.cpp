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

bool prime(long x) {
    if (x > 1e13) cerr << x << endl;

    if (x <= 3) return true;
    if (x % 2 == 0) return false;

    for (long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
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
