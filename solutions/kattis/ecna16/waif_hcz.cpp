// https://open.kattis.com/problems/waif

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

Dinic<1000> dinic;

int n, m, p;
bool toy_in_cat[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> p;

    for (int child = 1; child <= n; ++child) {
        dinic.add(0, child, 1);

        int toy_tot;
        cin >> toy_tot;

        for(int i = 1; i <= toy_tot; ++i) {
            int toy;
            cin >> toy;

            dinic.add(child, n + toy, 1);
        }
    }

    for (int cat = 1; cat <= p; ++cat) {
        int cat_tot;
        cin >> cat_tot;

        for (int i = 1; i <= cat_tot; ++i) {
            int toy;
            cin >> toy;

            dinic.add(n + toy, n + m + cat, 1);
            toy_in_cat[toy] = true;
        }

        int cat_limit;
        cin >> cat_limit;

        dinic.add(n + m + cat, 999, cat_limit);
    }

    for (int toy = 1; toy <= m; ++toy) {
        if (!toy_in_cat[toy]) {
            dinic.add(n + toy, n + m + p + 1, 1);
        }
    }

    dinic.add(n + m + p + 1, 999, 1000);

    cout << dinic.solve(0, 999) << endl;

    return 0;
}
