// https://open.kattis.com/problems/watersheds

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int h, w;
int grid[100][100];
char e[100][100];
char v[100][100];
char c;

void dfs(int i, int j) {
    if (v[i][j]) return;

    v[i][j] = c;

    if (e[i][j] & 1) dfs(i - 1, j);
    if (e[i][j] & 2) dfs(i, j - 1);
    if (e[i][j] & 4) dfs(i, j + 1);
    if (e[i][j] & 8) dfs(i + 1, j);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ':' << endl;

        cin >> h >> w;

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> grid[i][j];
                e[i][j] = 0;
                v[i][j] = 0;
            }
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int sink = grid[i][j];

                if (i) sink = min(sink, grid[i - 1][j]);
                if (j) sink = min(sink, grid[i][j - 1]);
                if (j < w - 1) sink = min(sink, grid[i][j + 1]);
                if (i < h - 1) sink = min(sink, grid[i + 1][j]);

                if (sink == grid[i][j]) {
                    // nothing
                } else if (i && sink == grid[i - 1][j]) {
                    e[i][j] |= 1;
                    e[i - 1][j] |= 8;
                } else if (j && sink == grid[i][j - 1]) {
                    e[i][j] |= 2;
                    e[i][j - 1] |= 4;
                } else if (j < w - 1 && sink == grid[i][j + 1]) {
                    e[i][j] |= 4;
                    e[i][j + 1] |= 2;
                } else if (i < h - 1 && sink == grid[i + 1][j]) {
                    e[i][j] |= 8;
                    e[i + 1][j] |= 1;
                }
            }
        }

        c = 'a';

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (!v[i][j]) {
                    dfs(i, j);
                    c += 1;
                }
            }
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (j) {
                    cout << ' ';
                }

                cout << v[i][j];
            }

            cout << endl;
        }
    }

    return 0;
}
