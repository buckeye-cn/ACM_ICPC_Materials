// https://open.kattis.com/problems/cursethedarkness

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

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        double x, y;
        cin >> x >> y;

        int n;
        cin >> n;

        bool found = false;

        for (int j = 0; j < n; ++j) {
            double xx, yy;
            cin >> xx >> yy;

            found |= sqr(xx - x) + sqr(yy - y) <= 64;
        }

        if (found) {
            cout << "light a candle" << endl;
        } else {
            cout << "curse the darkness" << endl;
        }
    }

    return 0;
}
