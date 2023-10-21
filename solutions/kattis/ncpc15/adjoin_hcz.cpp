// https://open.kattis.com/problems/adjoin

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> conn[100000];
vector<int> height[100000];
bool visited[100000];

void dfs1(int i, int ii) {
    if (!height[i][ii]) {
        int j = conn[i][ii];

        height[i][ii] = 1;

        for (int jj = 0; jj < conn[j].size(); ++jj) {
            if (conn[j][jj] != i) {
                dfs1(j, jj);
                height[i][ii] = max(height[i][ii], height[j][jj] + 1);
            }
        }
    }
}

int dfs2(int i) {
    visited[i] = true;

    int best = 1;

    for (int j: height[i]) {
        if (best < j * 2) {
            best = j * 2;
        } else if (best == j * 2) {
            best += 1;
        }
    }

    for (int j: conn[i]) {
        if (!visited[j]) {
            best = min(best, dfs2(j));
        }
    }

    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int c, l;
    cin >> c >> l;

    for (int i = 0; i < l; ++i) {
        int a, b;
        cin >> a >> b;

        conn[a].push_back(b);
        conn[b].push_back(a);
        height[a].push_back(0);
        height[b].push_back(0);
    }

    for (int i = 0; i < c; ++i) {
        for (int ii = 0; ii < conn[i].size(); ++ii) {
            dfs1(i, ii);
        }
    }

    int x = -4;
    int y = -4;
    int z = -4;

    for (int i = 0; i < c; ++i) {
        if (!visited[i]) {
            int d = dfs2(i);

            if (x < d) {
                z = y;
                y = x;
                x = d;
            } else if (y < d) {
                z = y;
                y = d;
            } else if (z < d) {
                z = d;
            }
        }
    }

    if (x / 2 == y / 2) {
        cout << (x | 1) + (x / 2 == z / 2) << endl;
    } else if (x / 2 == y / 2 + 1) {
        cout << (x & -2) << endl;
    } else {
        cout << x - 1 << endl;
    }

    return 0;
}
