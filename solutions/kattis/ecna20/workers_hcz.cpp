// https://open.kattis.com/problems/workers

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

DinicMinCost<202> dinic[51];

int dist[2][50][50][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cin >> dist[i][j][k][0] >> dist[i][j][k][1];
            }
        }
    }

    int best = 0;
    int best_cost = 1e8;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            dinic[i].add(200, j, 1, 0);
            dinic[i].add(50 + j, 100 + j, 1, 0);
            dinic[i].add(150 + j, 201, 1, 0);

            for (int k = 0; k < n; ++k) {
                dinic[i].add(j, 50 + k, 1, dist[0][j][k][k >= i]);
                dinic[i].add(100 + k, 150 + j, 1, dist[1][j][k][k >= i]);
            }
        }

        int cost = dinic[i].solve(200, 201).second;

        if (best_cost > cost) {
            best = i;
            best_cost = cost;
        }
    }

    cout << best_cost << endl;

    for (int i = 0; i < n; ++i) {
        int p1, p2;

        for (int j = 0; j < dinic[best].edges.size(); j += 2) {
            if (!dinic[best].edges[j].cap && dinic[best].edges[j].from == i) {
                p1 = dinic[best].edges[j].to - 50;
            }
        }

        for (int j = 0; j < dinic[best].edges.size(); j += 2) {
            if (!dinic[best].edges[j].cap && dinic[best].edges[j].from - 100 == p1) {
                p2 = dinic[best].edges[j].to - 150;
            }
        }

        cout << i + 1 << ' ' << p1 + 1 << "AB"[p1 >= best] << ' ' << p2 + 1 << endl;
    }

    return 0;
}
