// https://open.kattis.com/problems/coast

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m;
char grid[1002][1002];

void color(int i, int j) {
    if (i >= 0 && i <= n + 1 && j >= 0 && j <= m + 1 && grid[i][j] == '0') {
        grid[i][j] = 'x';
        color(i, j - 1);
        color(i, j + 1);
        color(i - 1, j);
        color(i + 1, j);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    memset(grid, '0', sizeof(grid));

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    color(0, 0);

    int total = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            total += grid[i][j] == '1' && grid[i][j - 1] == 'x';
            total += grid[i][j] == '1' && grid[i][j + 1] == 'x';
            total += grid[i][j] == '1' && grid[i - 1][j] == 'x';
            total += grid[i][j] == '1' && grid[i + 1][j] == 'x';
        }
    }

    cout << total << endl;

    return 0;
}
