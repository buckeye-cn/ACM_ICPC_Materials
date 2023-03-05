// https://open.kattis.com/problems/floodingfields

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

Dinic<480002> dinic;

int height[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, k, h;
    cin >> n >> k >> h;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> height[i][j];
        }
    }

    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;

        dinic.add(480000, r * 100 + c, 1);
    }

    for (int i = 0; i < h; ++i) {
        int level;
        cin >> level;

        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (height[j][k] <= level) continue;

                dinic.add(i * 20000 + j * 100 + k, i * 20000 + 10000 + j * 100 + k, 1);

                if (j) {
                    dinic.add(i * 20000 + (j - 1) * 100 + k, i * 20000 + 10000 + j * 100 + k, 1);
                }

                if (j < n - 1) {
                    dinic.add(i * 20000 + (j + 1) * 100 + k, i * 20000 + 10000 + j * 100 + k, 1);
                }

                if (k) {
                    dinic.add(i * 20000 + j * 100 + k - 1, i * 20000 + 10000 + j * 100 + k, 1);
                }

                if (k < n - 1) {
                    dinic.add(i * 20000 + j * 100 + k + 1, i * 20000 + 10000 + j * 100 + k, 1);
                }

                if (i < h - 1) {
                    dinic.add(i * 20000 + 10000 + j * 100 + k, i * 20000 + 20000 + j * 100 + k, 1);
                } else {
                    dinic.add(i * 20000 + 10000 + j * 100 + k, 480001, 1);
                }
            }
        }
    }

    cout << dinic.solve(480000, 480001) << endl;

    return 0;
}
