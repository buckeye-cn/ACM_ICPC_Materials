// https://open.kattis.com/problems/pearwise

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <long N>
struct Tarjan {
    vector<long> outs[N];

    void add(long from, long to) {
        outs[from].push_back(to);
    }

    long id_self[N];
    long id_low[N];
    long route[N];

    void dfs(long (&scc)[N], long from, long &last, long &now, long &now_scc) {
        id_self[from] = now;
        id_low[from] = now;
        now += 1;

        route[from] = last;
        last = from;

        for (long j = 0; j < outs[from].size(); ++j) {
            long to = outs[from][j];

            if (!id_self[to]) {
                dfs(scc, to, last, now, now_scc);

                id_low[from] = min(id_low[from], id_low[to]);
            } else if (!scc[to]) {
                id_low[from] = min(id_low[from], id_self[to]);
            }
        }

        if (id_low[from] == id_self[from]) {
            while (last != from) {
                scc[last] = now_scc;
                last = route[last];
            }

            scc[last] = now_scc;
            last = route[last];
            now_scc += 1;
        }
    }

    void solve(long (&scc)[N]) {
        memset(id_self, 0, sizeof(id_self));

        long last = 0;
        long now = 1;
        long now_scc = 1;

        for (long i = 0; i < N; ++i) {
            if (!id_self[i]) {
                dfs(scc, i, last, now, now_scc);
            }
        }

        for (long i = 0; i < N; ++i) {
            scc[i] -= 1;
        }
    }
};

Tarjan<26> tarjan;

int p[2000];
int pos[26][2000];

long scc[26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        string s;
        cin >> p[i] >> s;

        for (int j = 0; j < n; ++j) {
            pos[s[j] - 'A'][i] = j;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int tot = 0;

            for (int k = 0; k < m; ++k) {
                // tot += p[k] if pos[j][k] > pos[i][k]
                // tot -= p[k] otherwise
                tot += p[k] * (((pos[j][k] - pos[i][k]) >> 16) | 1);
            }

            if (tot > 0) {
                tarjan.add(i, j);
            } else {
                tarjan.add(j, i);
            }
        }
    }

    tarjan.solve(scc);

    long max_scc = 0;

    for (int i = 0; i < n; ++i) {
        max_scc = max(max_scc, scc[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (scc[i] == max_scc) {
            cout << char('A' + i) << ": can win" << endl;
        } else {
            cout << char('A' + i) << ": can't win" << endl;
        }
    }

    return 0;
}
