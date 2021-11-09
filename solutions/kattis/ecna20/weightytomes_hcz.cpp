// https://open.kattis.com/problems/weightytomes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int poly[21][5001];
int level[21][5001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    if (m == 1) {
        cout << n << ' ' << 1 << endl;

        return 0;
    }

    for (int i = 1; i <= m; ++i) {
        poly[i][1] = 1;

        for (int j = 2; j <= n; ++j) {
            poly[i][j] = poly[i][j - 1] + poly[i - 1][j - 1];
        }
    }

    // level[i][j] = min_among_k(max(level[i - 1][k - 1], level[i][j - k]) + 1)
    for (int i = 1; i <= m; ++i) {
        int p = 1;

        for (int j = 1; j <= n; ++j) {
            poly[i][p] -= 1;
            level[i][j] = p;

            if (!poly[i][p]) {
                p += 1;
            }
        }
    }

    int best = n;
    int best_lo = 1;
    int best_hi = 1;

    for (int i = 1; i <= n; ++i) {
        int curr = max(level[m - 1][i - 1], level[m][n - i]) + 1;

        if (best > curr) {
            best = curr;
            best_lo = i;
            best_hi = i;
        } else if (best == curr) {
            best_hi = i;
        }
    }

    cout << best << ' ';

    if (best_lo == best_hi) {
        cout << best_lo << endl;
    } else {
        cout << best_lo << '-' << best_hi << endl;
    }

    return 0;
}
