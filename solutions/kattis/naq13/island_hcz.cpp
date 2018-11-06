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
char data[100][100];
int i_tot;
int b_tot;
int bus_tot;
int group[100][100];
int uf[10000];

void dfs(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return;
    if (data[i][j] != '#' && data[i][j] != 'X') return;
    if (group[i][j] >= 0) return;

    group[i][j] = i_tot;

    dfs(i, j - 1);
    dfs(i, j + 1);
    dfs(i - 1, j);
    dfs(i + 1, j);
}

int find(int i) {
    if (uf[i] == i) return i;

    return uf[i] = find(uf[i]);
}

void merge(int from, int to) {
    from = find(from);
    to = find(to);

    if (from != to) {
        uf[from] = to;
    }
}

void solve() {
    i_tot = 0;
    b_tot = 0;
    bus_tot = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            group[i][j] = -1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((data[i][j] == '#' || data[i][j] == 'X') && group[i][j] < 0) {
                dfs(i, j);
                i_tot += 1;
            }
        }
    }

    for (int i = 0; i < i_tot; ++i) {
        uf[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (data[i][j] == 'X') {
                int ii;
                for (ii = i + 1; data[ii][j] == 'B'; ++ii);

                if (ii > i + 1 && data[ii][j] == 'X') {
                    b_tot += 1;
                    merge(group[i][j], group[ii][j]);
                }

                int jj;
                for (jj = j + 1; data[i][jj] == 'B'; ++jj);

                if (jj > j + 1 && data[i][jj] == 'X') {
                    b_tot += 1;
                    merge(group[i][j], group[i][jj]);
                }
            }
        }
    }

    for (int i = 0; i < i_tot; ++i) {
        if (uf[i] == i) {
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
    //         cerr << char('0' + group[i][j]);
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (cin.getline(data[n], 100)) {
        if (data[n][0]) {
            n += 1;
        } else {
            m = strlen(data[0]);

            solve();

            n = 0;
        }
    }

    m = strlen(data[0]);

    solve();

    return 0;
}
