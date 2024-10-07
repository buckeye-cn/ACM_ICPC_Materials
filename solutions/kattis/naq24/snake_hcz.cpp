// https://open.kattis.com/problems/snake

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char grid[12][12];

bool dfs(int ii, int jj, int head, int tail) {
    if (grid[ii][jj] >= tail) return false;
    if (grid[ii][jj] >= 0) return true;

    grid[ii][jj] = head;

    if (dfs(ii - 1, jj, head + 1, tail + 1)) return true;
    if (dfs(ii + 1, jj, head + 1, tail + 1)) return true;
    if (dfs(ii, jj - 1, head + 1, tail + 1)) return true;
    if (dfs(ii, jj + 1, head + 1, tail + 1)) return true;

    grid[ii][jj] = -1;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(grid, 101, sizeof(grid));

    int r, c;
    cin >> r >> c;

    int ii = 0;
    int jj = 0;
    int head = 16;
    int tail = 13;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            char cc;
            cin >> cc;

            if (cc == 'A') {
                grid[i][j] = 0;
            } else if (cc == '0') {
                grid[i][j] = -1;
                ii = i;
                jj = j;
            } else if (cc > '0' && cc <= '9') {
                cc -= '0';

                grid[i][j] = 16 - cc;
                tail = min(tail, 16 - cc);
            } else if (cc >= 'a' && cc <= 'f') {
                cc -= 'a' - 10;

                grid[i][j] = 16 - cc;
                tail = min(tail, 16 - cc);
            } else {
                grid[i][j] = -1;
            }
        }
    }

    cout << dfs(ii, jj, head, tail) << endl;

    return 0;
}
