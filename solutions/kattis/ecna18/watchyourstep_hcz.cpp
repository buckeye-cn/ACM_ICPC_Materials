// https://open.kattis.com/problems/watchyourstep

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

Tarjan<2500> tarjan;

char buf[5000];

bool conn[2500][2500];
long scc[2500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;
    cin.get();

    for (int i = 0; i < n; ++i) {
        cin.getline(buf, sizeof(buf));

        for (int j = 0; j < n; ++j) {
            conn[i][j] = buf[j * 2] - '0';

            if (conn[i][j]) {
                tarjan.add(i, j);
            }
        }
    }

    tarjan.solve(scc);

    int result = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && !conn[i][j] && scc[i] >= scc[j]) {
                result += 1;
                // cerr << i << ' ' << j << endl;
            }
        }
    }

    cout << result << endl;

    return 0;
}
