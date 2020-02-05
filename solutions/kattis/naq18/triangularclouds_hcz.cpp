// https://open.kattis.com/problems/triangularclouds

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int point_hash[65536];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    auto add = [&](long x1, long y1, long x2, long y2) {
        // hash of line & position on line
        if (x1 == x2) {
            point_hash[(x1 + y1) & 65535] += 1;
            point_hash[(x2 + y2) & 65535] -= 1;
        } else {
            point_hash[(x1 + (x1 * y2 - x2 * y1) / (x2 - x1)) & 65535] += 1;
            point_hash[(x2 + (x1 * y2 - x2 * y1) / (x2 - x1)) & 65535] -= 1;
        }
    };

    for (int i = -1; i <= 1; i += 2) {
        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            long x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

            long cross = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

            if (cross * i > 0) {
                add(x1, y1, x2, y2);
                add(x2, y2, x3, y3);
                add(x3, y3, x1, y1);
            } else if (cross * i < 0) {
                add(x2, y2, x1, y1);
                add(x3, y3, x2, y2);
                add(x1, y1, x3, y3);
            }
        }
    }

    for (int i = 0; i < 65536; ++i) {
        if (point_hash[i]) {
            cout << "no" << endl;

            return 0;
        }
    }

    cout << "yes" << endl;

    return 0;
}
