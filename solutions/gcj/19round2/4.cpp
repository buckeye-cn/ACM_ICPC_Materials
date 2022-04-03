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

long g[100000];
long scc[100000];
vector<int> grp[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        for (int i = 0; i < 100000; ++i) {
            tarjan.outs[i].clear();
        }

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int r1, r2;
            cin >> r1 >> r2;

            tarjan.add(i, r1 - 1);
            tarjan.add(i, r2 - 1);

            g[i] = 0;
            scc[i] = 0;
            grp[i].clear();
        }

        for (int i = 0; i < n; ++i) {
            cin >> g[i];
        }

        tarjan.solve(scc);

        for (int i = 0; i < n; ++i) {
            grp[scc[i]].push_back(i);
        }

        for (int i = n - 1; i >= 0; --i) {
            if (grp[i].empty()) continue;

            long tot = 0;

            for (int j = 0; j < grp[i].size(); ++j) {
                if (g[grp[i][j]] < 0) {
                    tot = -1;
                } else if (tot >= 0) {
                    tot += g[grp[i][j]];
                }
            }

            if (tot) {
                for (int j = 0; j < grp[i].size(); ++j) {
                    int p0 = tarjan.outs[grp[i][j]][0];
                    int p1 = tarjan.outs[grp[i][j]][1];

                    if (scc[p0] == i && scc[p1] == i) {
                        tot = -1;
                    }
                }
            }

            if (!grp[i][0]) {
                if (tot < 0) {
                    cout << "UNBOUNDED" << endl;
                } else {
                    cout << tot % MOD << endl;
                }

                break;
            }

            if (tot) {
                int p0 = tarjan.outs[grp[i][0]][0];
                int p1 = tarjan.outs[grp[i][0]][1];

                if (scc[p0] == i || scc[p1] == i) {
                    tot = -1;
                } else {
                    tot = (tot - 1) % MOD + 1;
                }

                for (int j = 0; j < grp[i].size(); ++j) {
                    int p0 = tarjan.outs[grp[i][j]][0];
                    int p1 = tarjan.outs[grp[i][j]][1];

                    if (tot < 0) {
                        g[p0] = -1;
                        g[p1] = -1;
                    } else {
                        if (g[p0] >= 0) {
                            g[p0] += tot;
                        }

                        if (g[p1] >= 0) {
                            g[p1] += tot;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
