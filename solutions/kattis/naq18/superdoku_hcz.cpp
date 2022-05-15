// https://open.kattis.com/problems/superdoku

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

Dinic<202> dinic[100];

int n, k;
int grid[100][100];
__int128 mask_i[100];
__int128 mask_j[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            grid[i][j] -= 1;

            __int128 mask = mask_i[i] | mask_j[j];
            __int128 m = __int128(1) << grid[i][j];

            if (!(mask & m)) {
                mask_i[i] ^= m;
                mask_j[j] ^= m;
            } else {
                cout << "no" << endl;

                return 0;
            }
        }
    }

    for (int i = k; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dinic[i].add(200, j, 1);
            dinic[i].add(100 + j, 201, 1);
        }

        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if ((mask_j[j] & (__int128(1) << k)) == 0) {
                    dinic[i].add(j, 100 + k, 1);
                }
            }
        }

        dinic[i].solve(200, 201);

        for (auto edge: dinic[i].edges) {
            if (!edge.cap && edge.from < 100 && edge.to < 200) {
                int j = edge.from;
                int k = edge.to - 100;

                grid[i][j] = k;
                mask_j[j] ^= __int128(1) << k;
            }
        }
    }

    cout << "yes" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) {
                cout << ' ';
            }
            cout << grid[i][j] + 1;
        }
        cout << endl;
    }

    return 0;
}
