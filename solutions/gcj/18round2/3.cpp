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

int value[120][120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> value[i][j];
            }
        }

        int result = 0;

        for (int v = -n; v <= n; ++v) {
            if (!v) continue;

            Dinic<202> dinic;

            for (int i = 0; i < n; ++i) {
                dinic.add(200, i, 1);
                dinic.add(i + 100, 201, 1);
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (value[i][j] == v) {
                        dinic.add(i, j + 100, 1);
                    }
                }
            }

            result += dinic.solve(200, 201);
        }

        cout << n * n - result << endl;
    }

    return 0;
}
