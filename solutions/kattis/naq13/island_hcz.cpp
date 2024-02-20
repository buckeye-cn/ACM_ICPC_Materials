// https://open.kattis.com/problems/island

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int maps;
int n, m;
char mapdata[100][100];
int i_tot;
int b_tot;
int bus_tot;
int mapgroup[100][100];
int group[10000];

void dfs(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return;
    if (mapdata[i][j] != '#' && mapdata[i][j] != 'X') return;
    if (mapgroup[i][j] >= 0) return;

    mapgroup[i][j] = i_tot;

    dfs(i, j - 1);
    dfs(i, j + 1);
    dfs(i - 1, j);
    dfs(i + 1, j);
}

int find(int g) {
    int root = g;

    while (root != group[root]) {
        root = group[root];
    }

    int curr = g;

    while (curr != root) {
        int prev = curr;

        curr = group[prev];
        group[prev] = root;
    }

    return root;
}

void merge(int from, int to) {
    from = find(from);
    to = find(to);

    if (from != to) {
        group[from] = to;
    }
}

void solve() {
    i_tot = 0;
    b_tot = 0;
    bus_tot = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mapgroup[i][j] = -1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((mapdata[i][j] == '#' || mapdata[i][j] == 'X') && mapgroup[i][j] < 0) {
                dfs(i, j);
                i_tot += 1;
            }
        }
    }

    for (int i = 0; i < i_tot; ++i) {
        group[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mapdata[i][j] == 'X') {
                int ii;
                for (ii = i + 1; mapdata[ii][j] == 'B'; ++ii);

                if (ii > i + 1 && mapdata[ii][j] == 'X') {
                    b_tot += 1;
                    merge(mapgroup[i][j], mapgroup[ii][j]);
                }

                int jj;
                for (jj = j + 1; mapdata[i][jj] == 'B'; ++jj);

                if (jj > j + 1 && mapdata[i][jj] == 'X') {
                    b_tot += 1;
                    merge(mapgroup[i][j], mapgroup[i][jj]);
                }
            }
        }
    }

    for (int i = 0; i < i_tot; ++i) {
        if (group[i] == i) {
            bus_tot += 1;
        }
    }

    maps += 1;

    if (maps > 1) {
        cout << endl;
    }

    cout << "Map " << maps << endl
        << "islands: " << i_tot << endl
        << "bridges: " << b_tot << endl
        << "buses needed: " << bus_tot << endl;

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cerr << char('0' + mapgroup[i][j]);
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (cin.getline(mapdata[n], 100)) {
        if (mapdata[n][0]) {
            n += 1;
        } else {
            m = strlen(mapdata[0]);

            solve();

            n = 0;
        }
    }

    m = strlen(mapdata[0]);

    solve();

    return 0;
}
