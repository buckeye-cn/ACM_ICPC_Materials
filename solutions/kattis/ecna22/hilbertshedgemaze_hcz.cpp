// https://open.kattis.com/problems/hilbertshedgemaze

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

void next(int n, long x, long y, long &xx, long &yy) {
    xx = 1l << (n - 1);
    yy = 1l << (n - 1);

    // DLUR -> 0123
    int d = 0;
    int i = n - 1;

    while (x != xx && y != yy) {
        d = "1300012122133032"[d * 4 + (y > yy) * 2 + (x > xx)] - '0';
        i -= 1;
        xx += (x > xx ? 1l : -1l) << i;
        yy += (y > yy ? 1l : -1l) << i;
    }

    if (d == 0) yy += (x != xx ? 0 : y > yy ? 1l : -1l) << i;
    if (d == 1) xx += (y != yy ? 0 : x > xx ? 1l : -1l) << i;
    if (d == 2) yy += (x != xx ? 0 : y < yy ? -1l : 1l) << i;
    if (d == 3) xx += (y != yy ? 0 : x < xx ? -1l : 1l) << i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int nn;
    cin >> nn;

    for (int i = 0; i < nn; ++i) {
        int n;
        cin >> n;

        int m[2];
        long x[2][100];
        long y[2][100];

        for (int j = 0; j < 2; ++j) {
            m[j] = 1;
            cin >> x[j][0] >> y[j][0];
            x[j][0] += 1;
            y[j][0] += 1;

            while (
                x[j][m[j] - 1] > 0
                && x[j][m[j] - 1] < (1l << n)
                && y[j][m[j] - 1] > 0
                && y[j][m[j] - 1] < (1l << n)
            ) {
                next(n, x[j][m[j] - 1], y[j][m[j] - 1], x[j][m[j]], y[j][m[j]]);
                m[j] += 1;
            }
        }

        bool poped = false;

        while (
            m[0] > 1
            && m[1] > 1
            && x[0][m[0] - 1] == x[1][m[1] - 1]
            && y[0][m[0] - 1] == y[1][m[1] - 1]
        ) {
            m[0] -= 1;
            m[1] -= 1;
            poped = true;
        }

        long result = 0;

        for (int j = 0; j < 2; ++j) {
            for (int k = 1; k < m[j]; ++k) {
                result += abs(x[j][k] - x[j][k - 1]) + abs(y[j][k] - y[j][k - 1]);
            }
        }

        if (
            poped
            || x[0][m[0] - 1] == x[1][m[1] - 1] && y[0][m[0] - 1] == y[1][m[1] - 1]
            || x[0][m[0] - 1] <= 0 && x[1][m[1] - 1] <= 0
            || x[0][m[0] - 1] >= (1l << n) && x[1][m[1] - 1] >= (1l << n)
            || y[0][m[0] - 1] <= 0 && y[1][m[1] - 1] <= 0
            || y[0][m[0] - 1] >= (1l << n) && y[1][m[1] - 1] >= (1l << n)
        ) {
            result += abs(x[0][m[0] - 1] - x[1][m[1] - 1]) + abs(y[0][m[0] - 1] - y[1][m[1] - 1]);
        } else {
            result += min(
                min(
                    min(
                        abs(x[0][m[0] - 1]) + abs(y[0][m[0] - 1]) + abs(x[1][m[1] - 1]) + abs(y[1][m[1] - 1]),
                        abs(x[0][m[0] - 1] - (1l << n)) + abs(y[0][m[0] - 1]) + abs(x[1][m[1] - 1] - (1l << n)) + abs(y[1][m[1] - 1])
                    ),
                    abs(x[0][m[0] - 1]) + abs(y[0][m[0] - 1] - (1l << n)) + abs(x[1][m[1] - 1]) + abs(y[1][m[1] - 1] - (1l << n))
                ),
                abs(x[0][m[0] - 1] - (1l << n)) + abs(y[0][m[0] - 1] - (1l << n)) + abs(x[1][m[1] - 1] - (1l << n)) + abs(y[1][m[1] - 1] - (1l << n))
            );
        }

        cout << result << endl;
    }

    return 0;
}
