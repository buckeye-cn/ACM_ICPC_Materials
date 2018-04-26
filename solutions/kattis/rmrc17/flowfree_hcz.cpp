// https://open.kattis.com/problems/flowfree

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define spos(x, y) (1 << (4 * (x) + y))

using namespace std;

char grid[4][4];
bool path[4][4][4][4][65536];
bool ok[5][65536];

void dfs(int sx, int sy, int tx, int ty, int x, int y, int mask) {
    if (x == tx && y == ty) {
        path[sx][sy][tx][ty][mask] = true;
    } else {
        if (mask & spos(x, y)) return;
        mask |= spos(x, y);

        if (x > 0) dfs(sx, sy, tx, ty, x - 1, y, mask);
        if (x < 3) dfs(sx, sy, tx, ty, x + 1, y, mask);
        if (y > 0) dfs(sx, sy, tx, ty, x, y - 1, mask);
        if (y < 3) dfs(sx, sy, tx, ty, x, y + 1, mask);
    }
}

bool test(int color) {
    for (int sx = 0; sx <= 3; ++sx) {
        for (int sy = 0; sy <= 3; ++sy) {
            if (grid[sx][sy] != "RGBY"[color]) continue;

            for (int tx = 0; tx <= 3; ++tx) {
                for (int ty = 0; ty <= 3; ++ty) {
                    if (spos(sx, sy) >= spos(tx, ty)) continue;
                    if (grid[tx][ty] != "RGBY"[color]) continue;

                    if (sx > 0) dfs(sx, sy, tx, ty, sx - 1, sy, 0);
                    if (sx < 3) dfs(sx, sy, tx, ty, sx + 1, sy, 0);
                    if (sy > 0) dfs(sx, sy, tx, ty, sx, sy - 1, 0);
                    if (sy < 3) dfs(sx, sy, tx, ty, sx, sy + 1, 0);

                    for (int mask = 0; mask < 65536; ++mask) {
                        if (!ok[color][mask]) continue;

                        for (int mask2 = 0; mask2 < 65536; ++mask2) {
                            if (mask & mask2) continue;
                            if (!path[sx][sy][tx][ty][mask2]) continue;

                            ok[color + 1][mask | mask2] = true;
                        }
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> grid[0] >> grid[1] >> grid[2] >> grid[3];

    int mask = 0;
    for (int x = 0; x <= 3; ++x) {
        for (int y = 0; y <= 3; ++y) {
            if (grid[x][y] != 'W') mask |= spos(x, y);
        }
    }
    ok[0][mask] = true;

    int color;
    for (color = 0; color < 4 && test(color); ++color);

    cout << (ok[color][65535] ? "solvable" : "not solvable") << endl;

    return 0;
}
