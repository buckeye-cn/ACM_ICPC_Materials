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
struct EdmondsKarpMinCost {
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

    long amount[N];
    long dist[N];
    long route[N];
    long visiting[N];
    bool active[N];

    pair<long, long> solve(long from, long to) {
        long flow = 0;
        long cost = 0;

        while (true) {
            memset(active, 0, sizeof(active));

            for (int i = 0; i < N; ++i) {
                dist[i] = 1l << 60;
            }

            long head = 0;
            long tail = 0;

            amount[from] = 1l << 60;
            amount[to] = 0;
            dist[from] = 0;
            visiting[(tail++) % N] = from;
            active[from] = true;

            while (head < tail) {
                long i = visiting[(head++) % N];
                active[i] = false;

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (e.cap && dist[e.to] > dist[i] + e.len) {
                        amount[e.to] = min(amount[i], e.cap);
                        dist[e.to] = dist[i] + e.len;
                        route[e.to] = outs[i][j];

                        if (!active[e.to]) {
                            visiting[(tail++) % N] = e.to;
                            active[e.to] = true;
                        }
                    }
                }
            }

            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from) {
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
            cost += amount[to] * dist[to];
        }

        return {flow, cost};
    }
};

EdmondsKarpMinCost<202> ek[51];

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
            ek[i].add(200, j, 1, 0);
            ek[i].add(50 + j, 100 + j, 1, 0);
            ek[i].add(150 + j, 201, 1, 0);

            for (int k = 0; k < n; ++k) {
                ek[i].add(j, 50 + k, 1, dist[0][j][k][k >= i]);
                ek[i].add(100 + k, 150 + j, 1, dist[1][j][k][k >= i]);
            }
        }

        int cost = ek[i].solve(200, 201).second;

        if (best_cost > cost) {
            best = i;
            best_cost = cost;
        }
    }

    cout << best_cost << endl;

    for (int i = 0; i < n; ++i) {
        int p1, p2;

        for (int j = 0; j < ek[best].edges.size(); j += 2) {
            if (!ek[best].edges[j].cap && ek[best].edges[j].from == i) {
                p1 = ek[best].edges[j].to - 50;
            }
        }

        for (int j = 0; j < ek[best].edges.size(); j += 2) {
            if (!ek[best].edges[j].cap && ek[best].edges[j].from - 100 == p1) {
                p2 = ek[best].edges[j].to - 150;
            }
        }

        cout << i + 1 << ' ' << p1 + 1 << "AB"[p1 >= best] << ' ' << p2 + 1 << endl;
    }

    return 0;
}
