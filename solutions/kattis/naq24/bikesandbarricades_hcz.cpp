// https://open.kattis.com/problems/bikesandbarricades

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

    int n;
    cin >> n;

    double p = 1000;

    for (int i = 0; i < n; ++i) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if ((x1 < 0) == (x2 < 0)) {
            continue;
        }

        double y = (x1 * y2 - x2 * y1) / (x1 - x2);

        if (y > 0) {
            p = min(p, y);
        }
    }

    if (p < 1000) {
        cout << p << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
