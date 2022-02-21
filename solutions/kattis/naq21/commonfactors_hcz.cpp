// https://open.kattis.com/problems/commonfactors

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

    long n;
    cin >> n;

    long k = 1;
    long u = 1;

    if (k * 2 <= n) {k *= 2; u *= (2 - 1);}
    if (k * 3 <= n) {k *= 3; u *= (3 - 1);}
    if (k * 5 <= n) {k *= 5; u *= (5 - 1);}
    if (k * 7 <= n) {k *= 7; u *= (7 - 1);}
    if (k * 11 <= n) {k *= 11; u *= (11 - 1);}
    if (k * 13 <= n) {k *= 13; u *= (13 - 1);}
    if (k * 17 <= n) {k *= 17; u *= (17 - 1);}
    if (k * 19 <= n) {k *= 19; u *= (19 - 1);}
    if (k * 23 <= n) {k *= 23; u *= (23 - 1);}
    if (k * 29 <= n) {k *= 29; u *= (29 - 1);}
    if (k * 31 <= n) {k *= 31; u *= (31 - 1);}
    if (k * 37 <= n) {k *= 37; u *= (37 - 1);}
    if (k * 41 <= n) {k *= 41; u *= (41 - 1);}
    if (k * 43 <= n) {k *= 43; u *= (43 - 1);}
    if (k * 47 <= n) {k *= 47; u *= (47 - 1);}

    long g = gcd(k, k - u);

    cout << (k - u) / g << '/' << k / g << endl;

    return 0;
}
