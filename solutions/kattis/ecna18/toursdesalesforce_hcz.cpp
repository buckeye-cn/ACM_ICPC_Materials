// https://open.kattis.com/problems/toursdesalesforce

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

template <long N>
struct HeldKarp {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        edges.push_back({to, len});
        outs[from].push_back(edges.size() - 1);
    }

    long dist[N][N];
    long best[1l << (N - 1)][N];

    long solve(long n) {
        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < n; ++j) {
                dist[i][j] = 1l << 60;
            }

            dist[i][i] = 0;

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

                dist[i][e.to] = min(dist[i][e.to], e.len);
            }
        }

        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < n; ++j) {
                for (long k = 0; k < n; ++k) {
                    dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
            }
        }

        for (long i = 0; i < (1l << (n - 1)); ++i) {
            for (long j = 0; j < n; ++j) {
                best[i][j] = 1l << 60;
            }

            for (long j = 0; j < n - 1; ++j) {
                if (i == 1l << j) {
                    best[i][j] = dist[n - 1][j];
                } else if (i & (1l << j)) {
                    for (long k = 0; k < n - 1; ++k) {
                        if ((i ^ (1l << j)) & (1l << k)) {
                            best[i][j] = min(best[i][j], dist[j][k] + best[i ^ (1l << j)][k]);
                        }
                    }
                }
            }
        }

        long result = 1l << 60;
        for (long i = 0; i < n - 1; ++i) {
            result = min(result, dist[i][n - 1] + best[(1l << (n - 1)) - 1][i]);
        }

        return result;
    }
};

template <long N>
struct DinicMinCost {
    struct Edge {
        long from, to, cap, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap, long len) {
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap, len});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0, -len});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long dist[N];
    long visiting[N];
    bool active[N];
    long step[N];

    long dfs(long from, long to, long limit, long &cost) {
        if (from == to) {
            return limit;
        }

        active[from] = true;

        long amount = limit;

        for (long j = step[from]; j < outs[from].size(); ++j) {
            Edge &e = edges[outs[from][j]];

            if (dist[e.to] == dist[from] + e.len && e.cap && !active[e.to]) {
                long flow = dfs(e.to, to, min(amount, e.cap), cost);

                if (flow) {
                    e.cap -= flow;
                    edges[outs[from][j] ^ 1].cap += flow;
                    amount -= flow;
                    cost += flow * e.len;

                    if (!amount) {
                        step[from] = j;

                        return limit;
                    }
                }
            }
        }

        step[from] = outs[from].size();
        active[from] = false;

        return limit - amount;
    }

    pair<long, long> solve(long from, long to) {
        long flow = 0;
        long cost = 0;

        while (true) {
            memset(active, 0, sizeof(active));
            memset(step, 0, sizeof(step));

            for (int i = 0; i < N; ++i) {
                dist[i] = 1l << 60;
            }

            long head = 0;
            long tail = 0;

            dist[from] = 0;
            visiting[(tail++) % N] = from;
            active[from] = true;

            while (head < tail) {
                long i = visiting[(head++) % N];
                active[i] = false;

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (e.cap && dist[e.to] > dist[i] + e.len) {
                        dist[e.to] = dist[i] + e.len;

                        if (!active[e.to]) {
                            visiting[(tail++) % N] = e.to;
                            active[e.to] = true;
                        }
                    }
                }
            }

            if (dist[to] == 1l << 60) break;

            flow += dfs(from, to, 1l << 60, cost);
        }

        return {flow, cost};
    }
};

HeldKarp<16> hk;
DinicMinCost<52> dinic;

int d;
int n[50];
long x[50][8];
long y[50][8];
long cost[50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> d;

    for (int i = 0; i < d; ++i) {
        cin >> n[i];

        for (int j = 0; j < n[i]; ++j) {
            cin >> x[i][j] >> y[i][j];
        }
    }

    for (int i = 0; i < d; ++i) {
        hk.edges.clear();
        for (int j = 0; j < 16; ++j) {
            hk.outs[j].clear();
        }

        for (int j = 0; j < n[i]; ++j) {
            for (int k = 0; k < n[i]; ++k) {
                hk.add(j, k, round(sqrt(sqr(x[i][j] - x[i][k]) + sqr(y[i][j] - y[i][k])) * 1e6));
            }
        }

        cost[i] = hk.solve(n[i]);

        if (i < d / 2) {
            dinic.add(50, i, 1, 0);
        } else {
            dinic.add(i, 51, 1, 0);
        }

        // cerr << i << endl;
    }

    for (int i = 0; i < d / 2; ++i) {
        for (int j = d / 2; j < d; ++j) {
            hk.edges.clear();
            for (int k = 0; k < 16; ++k) {
                hk.outs[k].clear();
            }

            for (int k = 0; k < n[i]; ++k) {
                for (int l = 0; l < n[i]; ++l) {
                    hk.add(k, l, round(sqrt(sqr(x[i][k] - x[i][l]) + sqr(y[i][k] - y[i][l])) * 1e6));
                }

                for (int l = 0; l < n[j]; ++l) {
                    hk.add(k, n[i] + l, round(sqrt(sqr(x[i][k] - x[j][l]) + sqr(y[i][k] - y[j][l])) * 1e6));
                }
            }

            for (int k = 0; k < n[j]; ++k) {
                for (int l = 0; l < n[i]; ++l) {
                    hk.add(n[i] + k, l, round(sqrt(sqr(x[j][k] - x[i][l]) + sqr(y[j][k] - y[i][l])) * 1e6));
                }

                for (int l = 0; l < n[j]; ++l) {
                    hk.add(n[i] + k, n[i] + l, round(sqrt(sqr(x[j][k] - x[j][l]) + sqr(y[j][k] - y[j][l])) * 1e6));
                }
            }

            dinic.add(i, j, 1, hk.solve(n[i] + n[j]) - cost[i] - cost[j]);

            // cerr << i << ' ' << j << endl;
        }
    }

    long tot = 0;

    for (int i = 0; i < d; ++i) {
        tot += cost[i];
    }

    cout << tot * 1e-6 << ' ' << (tot + dinic.solve(50, 51).second) * 1e-6 << endl;

    return 0;
}
