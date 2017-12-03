// https://open.kattis.com/problems/tray

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int m, n;

int used[24];
long count[26][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;

        used[(int) x] |= 1 << (int) y;
    }

    count[0][0] = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j & used[i]) continue;

            // ... ..| .|. .|| |.. |.| ||. |||
            // .-- |-- --. --|

            if (((j | used[i]) & 0) == 0) count[i + 1][0] += count[i][j];
            if (((j | used[i]) & 1) == 0) count[i + 1][1] += count[i][j];
            if (((j | used[i]) & 2) == 0) count[i + 1][2] += count[i][j];
            if (((j | used[i]) & 3) == 0) count[i + 1][3] += count[i][j];
            if (((j | used[i]) & 4) == 0) count[i + 1][4] += count[i][j];
            if (((j | used[i]) & 5) == 0) count[i + 1][5] += count[i][j];
            if (((j | used[i]) & 6) == 0) count[i + 1][6] += count[i][j];
            if (((j | used[i]) & 7) == 0) count[i + 1][7] += count[i][j];
            if (((j | used[i]) & 3) == 0) count[i + 1][0] += count[i][j];
            if (((j | used[i]) & 7) == 0) count[i + 1][4] += count[i][j];
            if (((j | used[i]) & 6) == 0) count[i + 1][0] += count[i][j];
            if (((j | used[i]) & 7) == 0) count[i + 1][1] += count[i][j];

            // cout << j << ' ' << (j | used[i]) << ' ' << count[i][j] << endl;
        }

        // cout << used[i] << endl << endl;
    }

    cout << count[m][0] << endl;

    return 0;
}
