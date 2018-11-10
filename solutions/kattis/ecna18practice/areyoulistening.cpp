// https://open.kattis.com/problems/areyoulistening

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

    int cx, cy, n;
    cin >> cx >> cy >> n;

    double d[4] {1e10, 1e10, 1e10, 1e10};

    for (int i = 0; i < n; ++i) {
        int x, y, r;
        cin >> x >> y >> r;

        d[3] = max(sqrt(sqr(x - cx) + sqr(y - cy)) - r, 0.);

        for (int j = 2; j >= 0; --j) {
            if (d[j] > d[j + 1]) {
                swap(d[j], d[j + 1]);
            }
        }
    }

    cout << floor(d[2]) << endl;

    return 0;
}
