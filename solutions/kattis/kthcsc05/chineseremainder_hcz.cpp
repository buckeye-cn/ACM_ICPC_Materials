// https://open.kattis.com/problems/chineseremainder

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long extgcd(long y, long x, long &s, long &t){
    long ss = 0;
    long tt = 1;

    s = 1;
    t = 0;

    while (x) {
        s -= y / x * ss;
        swap(s, ss);
        t -= y / x * tt;
        swap(t, tt);
        y %= x;
        swap(y, x);
    }

    return y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        long a, n, b, m;
        cin >> a >> n >> b >> m;

        long s, t;
        long g = extgcd(n, m, s, t);

        long k = n * m / g;
        long v = m / g * a * __int128(t) % k + n / g * b * __int128(s) % k;

        v = (v % k + k) % k;

        if (v % n == a && v % m == b) {
            cout << v << ' ' << k << endl;
        } else {
            cout << "no solution" << endl;
        }
    }

    return 0;
}
