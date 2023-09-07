// https://open.kattis.com/problems/soyoulikeyourfoodhot

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

    int pt, rt, p1, r1, p2, r2;
    char tmp;
    cin >> pt >> tmp >> rt >> p1 >> tmp >> r1 >> p2 >> tmp >> r2;

    pt = 100 * pt + rt;
    p1 = 100 * p1 + r1;
    p2 = 100 * p2 + r2;

    bool done = false;

    for (int i = 0; p1 * i <= pt; ++i) {
        if (!((pt - p1 * i) % p2)) {
            cout << i << ' ' << (pt - p1 * i) / p2 << endl;
            done = true;
        }
    }

    if (!done) {
        cout << "none" << endl;
    }

    return 0;
}
