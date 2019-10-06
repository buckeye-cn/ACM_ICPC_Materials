// https://open.kattis.com/problems/slowleak

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long dist[500][500];
bool repair[500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, t;
    long d;
    cin >> n >> m >> t >> d;

    repair[0] = true;
    repair[n - 1] = true;

    for (int i = 0; i < t; ++i) {
        int x;
        cin >> x;

        repair[x - 1] = true;
    }

    for (int i = 0; i < m; ++i) {
        int x, y;
        long len;
        cin >> x >> y >> len;

        dist[x - 1][y - 1] = len;
        dist[y - 1][x - 1] = len;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (dist[j][i] && dist[i][k]) {
                    if (dist[j][k]) {
                        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                    } else {
                        dist[j][k] = dist[j][i] + dist[i][k];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!repair[i]) continue;

        for (int j = 0; j < n; ++j) {
            if (!repair[j]) continue;

            if (dist[i][j] > d) {
                dist[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!repair[i]) continue;

        for (int j = 0; j < n; ++j) {
            if (!repair[j]) continue;

            for (int k = 0; k < n; ++k) {
                if (!repair[k]) continue;

                if (dist[j][i] && dist[i][k]) {
                    if (dist[j][k]) {
                        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                    } else {
                        dist[j][k] = dist[j][i] + dist[i][k];
                    }
                }
            }
        }
    }

    if (dist[0][n - 1]) {
        cout << dist[0][n - 1] << endl;
    } else {
        cout << "stuck" << endl;
    }

    return 0;
}
