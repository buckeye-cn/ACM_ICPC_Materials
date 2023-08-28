// https://open.kattis.com/problems/whichwarehouse

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

        active[from] = false;
        step[from] = outs[from].size();

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

DinicMinCost<202> dinic;

int prod[100][100];
int dist[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> prod[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];

            if (dist[i][j] == -1) {
                dist[i][j] = 1e6;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        dinic.add(200, i, 1, 0);
    }

    for (int i = 0; i < m; ++i) {
        dinic.add(100 + i, 201, 1, 0);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int cost = 0;

            for (int k = 0; k < n; ++k) {
                cost += dist[k][i] * prod[k][j];
            }

            dinic.add(i, 100 + j, 1, cost);
        }
    }

    cout << dinic.solve(200, 201).second << endl;

    return 0;
}
