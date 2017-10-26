// https://open.kattis.com/problems/birthdaycake

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n, m;
long r;
long x[100];
long y[100];
long a[100];
long b[100];
long c[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> r;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    int cross = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (a[i] * b[j] != b[i] * a[j]) {
                long vx = b[i] * c[j] - b[j] * c[i];
                long vy = c[i] * a[j] - c[j] * a[i];
                long base = a[i] * b[j] - a[j] * b[i];

                if (vx * vx + vy * vy < r * r * base * base) {
                    ++cross;
                }
            }
        }
    }

    if (cross + m + 1 != n) {
        cout << "no" << endl;

        return 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool ok = false;

            for (int k = 0; k < m; ++k) {
                long vi = x[i] * a[k] + y[i] * b[k] + c[k];
                long vj = x[j] * a[k] + y[j] * b[k] + c[k];

                if ((vi > 0) != (vj > 0)) {
                    ok = true;

                    break;
                }
            }

            if (!ok) {
                cout << "no" << endl;

                return 0;
            }
        }
    }

    cout << "yes" << endl;

    return 0;
}
