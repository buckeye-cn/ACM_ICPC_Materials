// https://open.kattis.com/problems/roomevacuation

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
struct Dinic {
    struct Edge {
        long from, to, cap;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap) {
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long layer[N];
    long visiting[N];
    long step[N];

    long dfs(long from, long to, long limit) {
        if (from == to) {
            return limit;
        }

        long amount = limit;

        for (long j = step[from]; j < outs[from].size(); ++j) {
            Edge &e = edges[outs[from][j]];

            if (layer[e.to] == layer[from] + 1 && e.cap) {
                long flow = dfs(e.to, to, min(amount, e.cap));

                if (flow) {
                    e.cap -= flow;
                    edges[outs[from][j] ^ 1].cap += flow;
                    amount -= flow;

                    if (!amount) {
                        step[from] = j;

                        return limit;
                    }
                }
            }
        }

        step[from] = outs[from].size();

        return limit - amount;
    }

    long solve(long from, long to) {
        long flow = 0;

        while (true) {
            memset(layer, 0, sizeof(layer));
            memset(step, 0, sizeof(step));

            long head = 0;
            long tail = 0;

            layer[from] = 1;
            visiting[tail++] = from;

            while (head < tail && !layer[to]) {
                long i = visiting[head++];

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (!layer[e.to] && e.cap) {
                        layer[e.to] = layer[i] + 1;

                        visiting[tail++] = e.to;
                    }
                }
            }

            if (!layer[to]) break;

            flow += dfs(from, to, 1l << 60);
        }

        return flow;
    }
};

Dinic<80402> dinic;

char room[20][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m, t;
    cin >> n >> m >> t;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> room[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (room[i][j] == 'P') {
                dinic.add(80400, i * 20 + j, 1);
            } else if (room[i][j] == 'E') {
                for (int k = 1; k <= t; ++k) {
                    dinic.add(k * 400 + i * 20 + j, 80401, 1);
                }
            }

            if (room[i][j] != '#') {
                for (int k = 0; k < t; ++k) {
                    dinic.add(k * 400 + i * 20 + j, (k + 1) * 400 + i * 20 + j, 1);

                    if (j && room[i][j - 1] != '#') {
                        dinic.add(k * 400 + i * 20 + j, (k + 1) * 400 + i * 20 + j - 1, 1);
                    }
                    if (j + 1 < m && room[i][j + 1] != '#') {
                        dinic.add(k * 400 + i * 20 + j, (k + 1) * 400 + i * 20 + j + 1, 1);
                    }
                    if (i && room[i - 1][j] != '#') {
                        dinic.add(k * 400 + i * 20 + j, (k + 1) * 400 + (i - 1) * 20 + j, 1);
                    }
                    if (i + 1 < n && room[i + 1][j] != '#') {
                        dinic.add(k * 400 + i * 20 + j, (k + 1) * 400 + (i + 1) * 20 + j, 1);
                    }
                }
            }
        }
    }

    cout << dinic.solve(80400, 80401) << endl;

    return 0;
}
