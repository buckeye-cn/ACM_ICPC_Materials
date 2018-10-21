// https://open.kattis.com/problems/rings

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int n;
double x[100];
double y[100];
double r[100];

bool conn[100][100];
bool visited[100];

int dfs(int i) {
    int result = 1;

    visited[i] = true;

    for (int j = 0; j < n; ++j) {
        if (!visited[j] && conn[i][j]) {
            result += dfs(j);
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        cin >> n;

        if (n < 0) {
            return 0;
        }

        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i] >> r[i];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double sqr_distance = sqr(x[j] - x[i]) + sqr(y[j] - y[i]);
                bool c = sqr_distance < sqr(r[j] + r[i])
                    && sqr_distance > sqr(r[j] - r[i]);

                conn[i][j] = c;
                conn[j][i] = c;
            }
        }

        memset(visited, 0, sizeof(visited));

        int best = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                best = max(best, dfs(i));
            }
        }

        if (best == 1) {
            cout << "The largest component contains 1 ring." << endl;
        } else {
            cout << "The largest component contains " << best << " rings." << endl;
        }
    }
}
