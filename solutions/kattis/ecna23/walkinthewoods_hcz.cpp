// https://open.kattis.com/problems/walkinthewoods

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int x[2501];
int y[2501];
// NESW
int to[2501][4];
int val[2501][4];
int visited[2501][4];

int p[10000];
int d[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(visited, -1, sizeof(visited));

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= m; ++i) {
        int j, k, v;
        cin >> j >> k >> v;

        if (y[j] < y[k]) {
            to[j][0] = k;
            val[j][0] = v;
            to[k][2] = j;
            val[k][2] = v;
        } else if (x[j] < x[k]) {
            to[j][1] = k;
            val[j][1] = v;
            to[k][3] = j;
            val[k][3] = v;
        } else if (y[j] > y[k]) {
            to[j][2] = k;
            val[j][2] = v;
            to[k][0] = j;
            val[k][0] = v;
        } else {
            to[j][3] = k;
            val[j][3] = v;
            to[k][1] = j;
            val[k][1] = v;
        }
    }

    char dd;
    cin >> p[0] >> dd;

    d[0] = dd == 'N' ? 0 : dd == 'E' ? 1 : dd == 'S' ? 2 : 3;
    visited[p[0]][d[0]] = 0;

    int pn = 1;

    while (true) {
        p[pn] = to[p[pn - 1]][d[pn - 1]];

        val[p[pn - 1]][d[pn - 1]] -= 1;
        val[p[pn]][d[pn - 1] ^ 2] -= 1;

        int valid = (val[p[pn]][0] > 0) + (val[p[pn]][1] > 0) + (val[p[pn]][2] > 0) + (val[p[pn]][3] > 0) - (val[p[pn]][d[pn - 1] ^ 2] > 0);

        if (!valid) {
            cout << x[p[pn]] << ' ' << y[p[pn]] << endl;

            return 0;
        }

        if (valid == 3) {
            d[pn] = d[pn - 1];
        } else if (val[p[pn]][(d[pn - 1] + 3) % 4]) {
            d[pn] = (d[pn - 1] + 3) % 4;
        } else if (val[p[pn]][d[pn - 1]]) {
            d[pn] = d[pn - 1];
        } else {
            d[pn] = (d[pn - 1] + 1) % 4;
        }

        if (visited[p[pn]][d[pn]] >= 0) {
            int best = 1e6;
            int pnn = visited[p[pn]][d[pn]];

            while (true) {
                for (int i = pn; i > pnn; --i) {
                    best = min(best, val[p[i]][d[i]]);
                }

                if (best < 3) break;

                for (int i = pn; i > pnn; --i) {
                    val[p[i]][d[i]] -= (best - 1) / 2;
                    val[p[i]][d[i - 1] ^ 2] -= (best - 1) / 2;
                }
            }

            for (int i = pn; i > pnn; --i) {
                visited[p[i]][d[i]] = -1;
            }

            pn = pnn;
        }

        visited[p[pn]][d[pn]] = pn;

        pn += 1;
    }
}
