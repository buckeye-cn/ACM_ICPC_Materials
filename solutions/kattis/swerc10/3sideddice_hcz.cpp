// https://open.kattis.com/problems/3sideddice

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long a1, b1, c1, a2, b2, c2, a3, b3, c3, a, b, c;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        cin >> a1 >> b1 >> c1;

        if (!a1 && !b1 && !c1) {
            return 0;
        }

        cin >> a2 >> b2 >> c2 >> a3 >> b3 >> c3 >> a >> b >> c;

        if (
            (a2 - a1) * (b3 - b1) == (b2 - b1) * (a3 - a1)
            && (a2 - a1) * (c3 - c1) == (c2 - c1) * (a3 - a1)
        ) {
            long amin = min(min(a1, a2), a3);
            long bmin = min(min(b1, b2), b3);
            long cmin = min(min(c1, c2), c3);
            long amax = max(max(a1, a2), a3);
            long bmax = max(max(b1, b2), b3);
            long cmax = max(max(c1, c2), c3);

            if (
                (a2 - a1) * (b - b1) == (b2 - b1) * (a - a1)
                && (a2 - a1) * (c - c1) == (c2 - c1) * (a - a1)
                && (a3 - a2) * (b - b2) == (b3 - b2) * (a - a2)
                && (a3 - a2) * (c - c2) == (c3 - c2) * (a - a2)
                && (a1 - a3) * (b - b3) == (b1 - b3) * (a - a3)
                && (a1 - a3) * (c - c3) == (c1 - c3) * (a - a3)
                && ((a == amin && a == amax) || (a > amin && a < amax))
                && ((b == bmin && b == bmax) || (b > bmin && b < bmax))
                && ((c == cmin && c == cmax) || (c > cmin && c < cmax))
            ) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            long s1 = (a2 - a1) * (b - b1) - (b2 - b1) * (a - a1);
            long s2 = (a3 - a2) * (b - b2) - (b3 - b2) * (a - a2);
            long s3 = (a1 - a3) * (b - b3) - (b1 - b3) * (a - a3);

            if (s1 && s2 && s3 && (s1 > 0) == (s2 > 0) && (s2 > 0) == (s3 > 0)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
}
