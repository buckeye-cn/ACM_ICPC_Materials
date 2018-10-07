// https://open.kattis.com/problems/dasblinkenlights

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int gcd(int y, int x) {
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

    int p, q, s;
    cin >> p >> q >> s;

    if (p * q / gcd(p, q) <= s) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
