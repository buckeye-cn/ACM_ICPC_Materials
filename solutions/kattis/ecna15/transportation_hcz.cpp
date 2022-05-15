// https://open.kattis.com/problems/transportation

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
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

Dinic<3002> dinic;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int s, r, f, t;
    cin >> s >> r >> f >> t;

    unordered_map<string, int> v;

    for (int i = 0; i < r; ++i) {
        string s;
        cin >> s;

        v.insert({s, i});
        dinic.add(3000, i, 1);
    }

    for (int i = r; i < r + f; ++i) {
        string s;
        cin >> s;

        v.insert({s, i});
        dinic.add(i, 3001, 1);
    }

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;

            if (v.find(s) == v.end()) {
                v.insert({s, v.size()});
            }

            int k = v[s];

            dinic.add(k, 1000 + i, 1);
            dinic.add(2000 + i, k, 1);
        }

        dinic.add(1000 + i, 2000 + i, 1);
    }

    cout << dinic.solve(3000, 3001) << endl;

    return 0;
}
