// https://open.kattis.com/problems/portal

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

void parallelogram_gcd(long &x1, long &y1, long &x2, long &y2, long x3, long y3) {
    while (true) {
        if (x1 * y2 == x2 * y1) {
            x1 = gcd(x1, x2);
            y1 = gcd(y1, y2);
            x2 = x3;
            y2 = y3;

            break;
        }

        if (x2 * y3 == x3 * y2) {
            x2 = gcd(x2, x3);
            y2 = gcd(y2, y3);

            break;
        }

        if (x3 * y1 == x1 * y3) {
            x1 = gcd(x1, x3);
            y1 = gcd(y1, y3);

            break;
        }

        long d = x1 * y2 - x2 * y1;
        long k = (x2 * y3 - x3 * y2) / d;
        long l = (x3 * y1 - x1 * y3) / d;

        x3 += k * x1 + l * x2;
        y3 += k * y1 + l * y2;

        swap(x2, x3);
        swap(y2, y3);
    }
}

long x[100000];
long y[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i < n; ++i) {
        x[i] -= x[0];
        y[i] -= y[0];
    }

    long x1 = x[1];
    long y1 = y[1];
    long x2 = 0;
    long y2 = 0;

    for (int i = 2; i < n; ++i) {
        parallelogram_gcd(x1, y1, x2, y2, x[i], y[i]);
    }

    if (x1 * y2 == x2 * y1) {
        cout << -1 << endl;
    } else {
        cout << abs(x1 * y2 - x2 * y1) << endl;
    }

    return 0;
}
