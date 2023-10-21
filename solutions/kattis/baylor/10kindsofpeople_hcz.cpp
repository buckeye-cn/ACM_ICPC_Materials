// https://open.kattis.com/problems/10kindsofpeople

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char mapdata[1002][1002];
int region[1002][1002];
int tot_region;

void dfs(int i, int j) {
    region[i][j] = tot_region;

    if (!region[i - 1][j] && mapdata[i - 1][j] == mapdata[i][j]) {
        dfs(i - 1, j);
    }
    if (!region[i + 1][j] && mapdata[i + 1][j] == mapdata[i][j]) {
        dfs(i + 1, j);
    }
    if (!region[i][j - 1] && mapdata[i][j - 1] == mapdata[i][j]) {
        dfs(i, j - 1);
    }
    if (!region[i][j + 1] && mapdata[i][j + 1] == mapdata[i][j]) {
        dfs(i, j + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int r, c;
    cin >> r >> c;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> mapdata[i][j];
        }
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (!region[i][j]) {
                tot_region += 1;

                dfs(i, j);
            }
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        if (region[r1][c1] == region[r2][c2]) {
            if (mapdata[r1][c1] == '0' && mapdata[r2][c2] == '0') {
                cout << "binary" << endl;
            } else if (mapdata[r1][c1] == '1' && mapdata[r2][c2] == '1') {
                cout << "decimal" << endl;
            }
        } else {
            cout << "neither" << endl;
        }
    }

    return 0;
}
