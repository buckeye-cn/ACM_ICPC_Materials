// https://open.kattis.com/problems/diagonalcut

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

    long m, n;
    cin >> m >> n;

    long g = gcd(m, n);

    cout << g * ((m / g % 2) & (n / g % 2)) << endl;

    return 0;
}
