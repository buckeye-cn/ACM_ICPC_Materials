// https://open.kattis.com/problems/hubtown

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

const double PI = acos(-1);

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

Dinic<400002> dinic;
vector<int> group[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    set<pair<double, int>> sc;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        sc.insert({atan2(x, y), i});
    }

    set<pair<double, int>> sl;

    for (int i = 0; i < m; ++i) {
        int x, y, c;
        cin >> x >> y >> c;

        sl.insert({atan2(x, y), i});

        dinic.add(200000 + i, 400001, c);
    }

    pair<double, int> slmin = *sl.begin();
    pair<double, int> slmax = *sl.rbegin();

    sl.insert({slmin.first + 2 * PI, slmin.second});
    sl.insert({slmax.first - 2 * PI, slmax.second});

    auto iter_c = sc.begin();
    auto iter_l = sl.begin();

    while (iter_c != sc.end()) {
        auto iter_c0 = iter_c;

        while (iter_c != sc.end() && iter_c0->first + 1e-14 > iter_c->first) {
            // cerr << iter_c0->second << '=' << iter_c->second << endl;

            group[iter_c0->second].push_back(iter_c->second);
            ++iter_c;
        }

        while (iter_c0->first + 1e-14 > iter_l->first) {
            ++iter_l;
        }

        auto iter_l0 = iter_l;

        // cerr << iter_l0->second << ".." << iter_l->second << endl;

        --iter_l0;

        dinic.add(400000, iter_c0->second, group[iter_c0->second].size());

        if (iter_c0->first - iter_l0->first + 1e-14 < iter_l->first - iter_c0->first) {
            dinic.add(iter_c0->second, 200000 + iter_l0->second, group[iter_c0->second].size());
        } else if (iter_c0->first - iter_l0->first > iter_l->first - iter_c0->first + 1e-14) {
            dinic.add(iter_c0->second, 200000 + iter_l->second, group[iter_c0->second].size());
        } else {
            dinic.add(iter_c0->second, 200000 + iter_l0->second, group[iter_c0->second].size());
            dinic.add(iter_c0->second, 200000 + iter_l->second, group[iter_c0->second].size());
        }
    }

    cout << dinic.solve(400000, 400001) << endl;

    for (auto e: dinic.edges) {
        if (e.from < 400000 && e.to < 200000 && e.cap) {
            for (int i = 0; i < e.cap && !group[e.to].empty(); ++i) {
                cout << group[e.to].back() << ' ' << e.from - 200000 << endl;
                group[e.to].pop_back();
            }
        }
    }

    return 0;
}
