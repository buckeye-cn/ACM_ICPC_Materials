#include <bits/stdc++.h>
using namespace std;

template<typename D>
struct EdmondsKarp {
    static constexpr D Inf = 1l << 60;

    struct Edge {
        size_t from, to; D cap;
    };

    size_t N;

    vector<Edge> edges;
    vector<vector<size_t>> outs;

    EdmondsKarp(size_t n) : N(n) {
        outs.resize(n);
    }

    void add(size_t from, size_t to, D cap) {
        assert(from < N);
        assert(to < N);
        if (cap > 0) {
            outs[from].emplace_back(edges.size());
            edges.emplace_back(Edge { from, to, cap });
            outs[to].emplace_back(edges.size());
            edges.emplace_back(Edge { to, from, 0 });
        }
    }

    vector<D> amount;
    vector<size_t> route;
    vector<size_t> visiting;

    D solve(size_t from, size_t to) {
        amount.resize(N);
        route.resize(N);
        visiting.resize(N);

        D flow = 0;

        while (true) {
            fill(amount.begin(), amount.end(), 0);

            size_t head = 0, tail = 0;

            amount[from] = Inf;
            visiting[tail++] = from;

            while (head < tail && !amount[to]) {
                size_t i = visiting[head++];

                for (size_t j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap) {
                        amount[e.to] = min(amount[i], e.cap);
                        route[e.to] = outs[i][j];

                        visiting[tail++] = e.to;
                    }
                }
            }

            if (!amount[to]) break;

            for (size_t i = to; i != from; i = edges[route[i]].from) {
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};
