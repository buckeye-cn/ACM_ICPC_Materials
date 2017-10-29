// https://open.kattis.com/problems/ontrack

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define c2(x) ((x) * ((x) - 1) / 2)

using namespace std;

int n, m;
vector<int> conn[25000];
vector<int> group[25000];

int count(int i, int from) {
    int result = 1;

    for (int j = 0; j < conn[i].size(); ++j) {
        if (conn[i][j] != from) {
            result += count(conn[i][j], i);
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        conn[x].push_back(y);
        conn[y].push_back(x);
        group[x].push_back(0);
        group[y].push_back(0);

        if (m < x + 1) m = x + 1;
        if (m < y + 1) m = y + 1;
    }

    int best = 0;
    int best_i = -1;

    for (int i = 0; i < m; ++i) {
        int result = 0;

        for (int j = 0; j < conn[i].size(); ++j) {
            group[i][j] = count(conn[i][j], i);
            result += c2(group[i][j]);
        }

        result = c2(m - 1) - result;
        if (best < result) {
            best = result;
            best_i = i;
        }
    }

    int best_r = 0;

    for (int j = 0; j < conn[best_i].size(); ++j) {
        for (int k = j + 1; k < conn[best_i].size(); ++k) {
            int result = c2(group[best_i][j] + group[best_i][k]) - c2(group[best_i][j]) - c2(group[best_i][k]);
            if (best_r < result) {
                best_r = result;
            }
        }
    }

    cout << best << ' ' << best - best_r << endl;

    return 0;
}
