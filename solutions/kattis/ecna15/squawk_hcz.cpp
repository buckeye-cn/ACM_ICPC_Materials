// https://open.kattis.com/problems/squawk

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool conn[100][100];
long v[10][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    v[0][s] = 1;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        conn[x][y] = true;
        conn[y][x] = true;
    }

    for (int i = 1; i <= t; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                v[i][j] += conn[j][k] * v[i - 1][k];
            }
        }
    }

    long result = 0;

    for (int i = 0; i < n; ++i) {
        result += v[t][i];
    }

    cout << result << endl;

    return 0;
}
