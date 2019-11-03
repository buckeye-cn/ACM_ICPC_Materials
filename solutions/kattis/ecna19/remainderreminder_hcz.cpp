// https://open.kattis.com/problems/remainderreminder

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;

    long v1 = 0;
    long v2 = 0;
    long v3 = 0;

    for (long h = 1; a > 2 * h; ++h) {
        long v = (a - 2 * h) * (b - 2 * h) * h;

        if (v > v1) {
            v3 = v2;
            v2 = v1;
            v1 = v;
        } else if (v < v1 && v > v2) {
            v3 = v2;
            v2 = v;
        } else if (v < v2 && v > v3) {
            v3 = v;
        }
    }

    long result = c;

    long step = v1;
    while (result % v2 != d) {
        result += step;
    }

    step = step * v2 / gcd(step, v2);
    while (result % v3 != e) {
        result += step;
    }

    step = step * v3 / gcd(step, v3);
    while (result < f) {
        result += step;
    }

    cout << result << endl;

    return 0;
}
