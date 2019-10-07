// https://open.kattis.com/problems/zipline

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
    cout.precision(15);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        double w, g, h, r;
        cin >> w >> g >> h >> r;

        double lo = sqrt(sqr(g - h) + sqr(w));
        double hi = sqrt(sqr(g + h - 2 * r) + sqr(w));

        cout << lo << ' ' << hi << endl;
    }

    return 0;
}
