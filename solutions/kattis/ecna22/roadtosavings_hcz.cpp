// https://open.kattis.com/problems/roadtosavings

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int road[100][100];
int dist[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = 1e6 * (i != j);
        }
    }

    for (int i = 0; i < m; ++i) {
        int s, t, l;
        cin >> s >> t >> l;

        road[s - 1][t - 1] = l;
        dist[s - 1][t - 1] = l;
        dist[t - 1][s - 1] = l;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    int result = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (
                road[i][j]
                && dist[a - 1][i] + road[i][j] + dist[j][b - 1] != dist[a - 1][b - 1]
                && dist[a - 1][j] + road[i][j] + dist[i][b - 1] != dist[a - 1][b - 1]
            ) {
                result += road[i][j];
            }
        }
    }

    cout << result << endl;

    return 0;
}
