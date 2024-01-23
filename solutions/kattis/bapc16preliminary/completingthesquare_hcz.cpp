// https://open.kattis.com/problems/completingthesquare

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    if (sqr(a - c) + sqr(b - d) == sqr(a - e) + sqr(b - f) + sqr(c - e) + sqr(d - f)) {
        cout << a + c - e << ' ' << b + d - f << endl;
    } else if (sqr(a - e) + sqr(b - f) == sqr(a - c) + sqr(b - d) + sqr(c - e) + sqr(d - f)) {
        cout << a + e - c << ' ' << b + f - d << endl;
    } else {
        cout << c + e - a << ' ' << d + f - b << endl;
    }

    return 0;
}
