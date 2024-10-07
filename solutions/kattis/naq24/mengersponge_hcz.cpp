// https://open.kattis.com/problems/mengersponge

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

    int l, x, xd, y, yd, z, zd;
    cin >> l >> x >> xd >> y >> yd >> z >> zd;

    for (int i = 0; i < l; ++i) {
        bool xmid = 3 * x > xd && 3 * x < 2 * xd;
        bool ymid = 3 * y > yd && 3 * y < 2 * yd;
        bool zmid = 3 * z > zd && 3 * z < 2 * zd;

        if (xmid + ymid + zmid >= 2) {
            cout << 0 << endl;

            return 0;
        }

        x *= 3;
        x %= xd;
        y *= 3;
        y %= yd;
        z *= 3;
        z %= zd;
    }

    cout << 1 << endl;

    return 0;
}
