// https://open.kattis.com/problems/mazeman

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char maze[102][102];

int dfs(int i, int j) {
    if (maze[i][j] == '.' || maze[i][j] == ' ') {
        int dot = maze[i][j] == '.';

        maze[i][j] = 'X';

        return dot | dfs(i, j - 1) | dfs(i, j + 1) | dfs(i - 1, j) | dfs(i + 1, j);
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin.get();

        for (int j = 1; j <= m; ++j) {
            maze[i][j] = cin.get();
        }
    }

    int count = 0;
    int dot = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (maze[i][j] >= 'A' && maze[i][j] <= 'W') {
                maze[i][j] = ' ';
                count += dfs(i, j);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dot += maze[i][j] == '.';
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         cerr << maze[i][j];
    //     }
    //     cerr << endl;
    // }

    cout << count << ' ' << dot << endl;

    return 0;
}
