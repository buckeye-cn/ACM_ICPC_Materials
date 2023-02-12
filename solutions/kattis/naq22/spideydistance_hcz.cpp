// https://open.kattis.com/problems/spideydistance

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

    int t, s;
    cin >> t >> s;

    long tt = 0;
    long ss = 0;

    for (int i = 0; i < min(t, s); ++i) {
        tt += min(min(s - (i + 1) / 2, (s - i) * 2), t - i);
    }

    for (int i = 0; i < s; ++i) {
        ss += min(s - (i + 1) / 2, (s - i) * 2);
    }

    tt *= 4;
    tt += 1;
    ss *= 4;
    ss += 1;

    if (tt == ss) {
        cout << 1 << endl;

        return 0;
    }

    long g = gcd(tt, ss);

    cout << tt / g << '/' << ss / g << endl;

    return 0;
}
