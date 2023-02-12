// https://open.kattis.com/problems/movienight

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define MOD 1000000007l

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

Tarjan<100000> tarjan;

long pow2[100000];
long scc[100000];
long parent[100000];
long tot[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    pow2[0] = 1;

    for (int i = 1; i < 100000; ++i) {
        pow2[i] = pow2[i - 1] * 2;
        pow2[i] %= MOD;
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int y;
        cin >> y;

        tarjan.add(i, y - 1);
    }

    tarjan.solve(scc);

    for (int i = 0; i < n; ++i) {
        parent[i] = n;
    }

    for (int i = 0; i < n; ++i) {
        parent[scc[i]] = min(parent[scc[i]], scc[tarjan.outs[i][0]]);
    }

    for (int i = 0; i < n; ++i) {
        if (parent[i] < n) {
            tot[i] = 1;
        }
    }

    long res = 1;

    for (int i = n - 1; i >= 0; --i) {
        tot[i] += 1;

        if (parent[i] == i) {
            res *= tot[i];
            res %= MOD;
        } else if (parent[i] < n) {
            tot[parent[i]] *= tot[i];
            tot[parent[i]] %= MOD;
        }
    }

    cout << (res + MOD - 1) % MOD << endl;

    return 0;
}
