// https://open.kattis.com/problems/factovisors

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long a, b;

    while (cin >> a >> b) {
        bool ok = b > 0;
        long brem = b;

        for (long i = 2; i <= brem && ok; ++i) {
            if (i * i > brem) i = brem;

            long p = 0;

            while (brem % i == 0) {
                brem /= i;
                p += 1;
            }

            long ipow = i;

            while (p > 0 && ipow <= a) {
                p -= a / ipow;
                ipow *= i;
            }

            ok = p <= 0;
        }

        if (ok) {
            cout << b << " divides " << a << '!' << endl;
        } else {
            cout << b << " does not divide " << a << '!' << endl;
        }
    }

    return 0;
}
