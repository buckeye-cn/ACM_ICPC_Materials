// https://open.kattis.com/problems/amongourselves

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int a[200001];
int b[200001];
vector<int> ab[200001];
vector<int> e[200001];
char id[200001];
map<int, int> group[200001];

void dfs_id(int i) {
    for (int j: e[i]) {
        if (j > 0) {
            if (!id[j]) {
                id[j] = id[i];
                dfs_id(j);
            }
        } else if (!id[-j]) {
            id[-j] = -id[i];
            dfs_id(-j);
        }
    }
}

pair<int, int> find(int limit, int now, int i) {
    int min_t = now;

    while (true) {
        map<int, int>::iterator iter = group[i].upper_bound(limit);

        if (iter == group[i].end()) {
            return {min_t, i};
        }

        min_t = min(min_t, iter->first);
        i = iter->second;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, k, t;
    cin >> n >> m >> k >> t;

    for (int i = 1; i <= m; ++i) {
        string s;
        cin >> a[i] >> b[i] >> s;

        a[m + i] = a[i];
        b[m + i] = b[i];
        ab[i].push_back(i);
        ab[m + i].push_back(m + i);

        if (s[0] == 'c') {
            e[a[i]].push_back(b[i]);
            e[b[i]].push_back(a[i]);
        } else {
            e[a[i]].push_back(-b[i]);
            e[b[i]].push_back(-a[i]);
        }
    }

    id[k] = 1;
    dfs_id(k);

    for (int i = t; i <= 2 * m - t; ++i) {
        int limit = i - m + t;

        for (int j: ab[i]) {
            pair<int, int> ga = find(limit, j, a[j]);
            pair<int, int> gb = find(limit, j, b[j]);

            int next = min(ga.first, gb.first);

            if (ga.second != gb.second) {
                group[min(ga.second, gb.second)][next] = max(ga.second, gb.second);
            }

            if (next <= m && next > limit) {
                ab[next + m - t].push_back(j);
            }
        }

        if (i >= m) {
            pair<int, int> g1 = find(limit, i, 1);
            pair<int, int> gk = find(limit, i, k);

            if (g1.second == gk.second) {
                cout << i - m + 1 << (id[1] == 1 ? " crewmate" : " imposter") << endl;

                return 0;
            }
        }
    }

    cout << -1 << endl;

    return 0;
}
