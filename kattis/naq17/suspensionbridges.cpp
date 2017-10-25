// https://open.kattis.com/problems/suspensionbridges

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

long double d, s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(15);

    cin >> d >> s;

    long double a_min = 0;
    long double a_max = 1e8;

    while (a_max - a_min > 1e-12) {
        long double a = (a_max + a_min) / 2;
        long double v = a * cosh(d / (2 * a)) - a - s;

        if (v > 0) {
            a_min = a;
        } else {
            a_max = a;
        }
    }

    cout << 2 * a_min * sinh(d / (2 * a_min)) << endl;

    return 0;
}
