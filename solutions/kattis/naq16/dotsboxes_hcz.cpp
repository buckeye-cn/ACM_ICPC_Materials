// https://open.kattis.com/problems/dotsboxes

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

Dinic<10000> dinic;

int n;
bool ud[100][100];
bool lr[100][100];
int slot[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 1; i <= n; ++i) {
        char c;

        for (int j = 1; j <= n; ++j) {
            cin >> c;

            if (j == n) break;

            cin >> c;
            ud[i][j] = c == '-';
        }

        if (i == n) break;

        for (int j = 1; j <= n; ++j) {
            cin >> c;
            lr[i][j] = c == '|';

            if (j == n) break;

            cin >> c;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            slot[i][j] = !ud[i][j] + !ud[i + 1][j] + !lr[i][j] + !lr[i][j + 1] - 1;

            if ((i ^ j) & 1) {
                dinic.add(100 * i + j, 9999, slot[i][j]);
            } else {
                dinic.add(9998, 100 * i + j, slot[i][j]);
            }

            // cerr << slot[i][j] << ' ';
        }

        // cerr << endl;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j == n) break;

            if (!ud[i][j]) {
                if ((i ^ j) & 1) {
                    dinic.add(100 * (i - 1) + j, 100 * i + j, 1);
                } else {
                    dinic.add(100 * i + j, 100 * (i - 1) + j, 1);
                }
            }
        }

        if (i == n) break;

        for (int j = 1; j <= n; ++j) {
            if (!lr[i][j]) {
                if ((i ^ j) & 1) {
                    dinic.add(100 * i + (j - 1), 100 * i + j, 1);
                } else {
                    dinic.add(100 * i + j, 100 * i + (j - 1), 1);
                }
            }
        }
    }

    cout << dinic.solve(9998, 9999) + 1 << endl;

    return 0;
}
