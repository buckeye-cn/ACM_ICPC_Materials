// https://open.kattis.com/problems/escapewallmaria

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int g[102][102];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t, n, m;
    cin >> t >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;

            if (c == 'S') {
                g[i][j] = -1;
            } else {
                g[i][j] = c;
            }
        }
    }

    for (int p = -1; p >= -1 - t; --p) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (g[i][j] == p && (i == 1 || i == n || j == 1 || j == m)) {
                    cout << -1 - p << endl;

                    return 0;
                }

                if (g[i][j] == '0' && g[i][j - 1] == p) g[i][j] = p - 1;
                if (g[i][j] == '0' && g[i][j + 1] == p) g[i][j] = p - 1;
                if (g[i][j] == '0' && g[i - 1][j] == p) g[i][j] = p - 1;
                if (g[i][j] == '0' && g[i + 1][j] == p) g[i][j] = p - 1;
                if (g[i][j] == 'L' && g[i][j - 1] == p) g[i][j] = p - 1;
                if (g[i][j] == 'R' && g[i][j + 1] == p) g[i][j] = p - 1;
                if (g[i][j] == 'U' && g[i - 1][j] == p) g[i][j] = p - 1;
                if (g[i][j] == 'D' && g[i + 1][j] == p) g[i][j] = p - 1;
            }
        }
    }

    cout << "NOT POSSIBLE" << endl;

    return 0;
}
