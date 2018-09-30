// https://open.kattis.com/problems/erraticants

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool grid[121][121][4];
int visit[121][121];

void dfs(int x, int y, int step) {
    if (visit[x][y] < step) return;

    visit[x][y] = step;

    if (grid[x][y][0]) {
        dfs(x, y + 1, step + 1);
    }

    if (grid[x][y][1]) {
        dfs(x + 1, y, step + 1);
    }

    if (grid[x][y][2]) {
        dfs(x - 1, y, step + 1);
    }

    if (grid[x][y][3]) {
        dfs(x, y - 1, step + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;

        memset(grid, 0, sizeof(grid));

        int x = 60;
        int y = 60;

        for (int j = 0; j < s; ++j) {
            char c;
            cin >> c;

            if (c == 'N') {
                grid[x][y][0] = true;
                grid[x][y + 1][3] = true;
                y += 1;
            } else if (c == 'E') {
                grid[x][y][1] = true;
                grid[x + 1][y][2] = true;
                x += 1;
            } else if (c == 'W') {
                grid[x][y][2] = true;
                grid[x - 1][y][1] = true;
                x -= 1;
            } else if (c == 'S') {
                grid[x][y][3] = true;
                grid[x][y - 1][0] = true;
                y -= 1;
            }

            visit[x][y] = j + 1;
        }

        dfs(60, 60, 0);

        cout << visit[x][y] << endl;
    }

    return 0;
}
