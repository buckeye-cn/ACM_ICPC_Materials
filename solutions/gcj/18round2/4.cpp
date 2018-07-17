#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int r, c;
bool grid[24][24];

int b1, b2, b3, b4;
int x, y;
bool filled[24][24];

int dfs(int i, int j) {
    if (i < 0 || i >= r || j < 0 || j >= c || filled[i][j]) {
        return 0;
    }
    if (grid[i][j] != (
        i < x
            ? j < y
                ? b1
                : b2
            : j < y
                ? b3
                : b4
    )) {
        return 0;
    }

    filled[i][j] = true;

    return dfs(i - 1, j) + dfs(i + 1, j) + dfs(i, j - 1) + dfs(i, j + 1) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        cin >> r >> c;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                char ch;
                cin >> ch;

                grid[i][j] = ch == 'B';
            }
        }

        bool mode[2][2][2][2];
        memset(mode, 0, sizeof(mode));

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                mode[grid[i][j]][grid[i][j]][grid[i][j]][grid[i][j]] = true;
            }
        }
        for (int i = 0; i < r - 1; ++i) {
            for (int j = 0; j < c; ++j) {
                mode[grid[i][j]][grid[i][j]][grid[i + 1][j]][grid[i + 1][j]] = true;
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c - 1; ++j) {
                mode[grid[i][j]][grid[i][j + 1]][grid[i][j]][grid[i][j + 1]] = true;
            }
        }
        for (int i = 0; i < r - 1; ++i) {
            for (int j = 0; j < c - 1; ++j) {
                mode[grid[i][j]][grid[i][j + 1]][grid[i + 1][j]][grid[i + 1][j + 1]] = true;
            }
        }

        int best = 0;

        for (b1 = 0; b1 < 2; ++b1)
        for (b2 = 0; b2 < 2; ++b2)
        for (b3 = 0; b3 < 2; ++b3)
        for (b4 = 0; b4 < 2; ++b4)
        if (mode[b1][b2][b3][b4]) {
            for (x = 0; x <= r; ++x) {
                for (y = 0; y <= c; ++y) {
                    memset(filled, 0, sizeof(filled));

                    for (int i = 0; i < r; ++i) {
                        for (int j = 0; j < c; ++j) {
                            best = max(best, dfs(i, j));
                        }
                    }
                }
            }
        }

        cout << best << endl;
    }

    return 0;
}
