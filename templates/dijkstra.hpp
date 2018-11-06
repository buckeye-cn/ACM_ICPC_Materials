#include <bits/stdc++.h>
using namespace std;

// (u)int64, float
template<typename D>
struct Dijkstra {
    static constexpr D Inf = 1l << 60;

    struct Edge { size_t to; D len; };
    struct Vertex {
        vector<Edge> outs;
        D dist = Inf;
#ifdef DIJKSTRA_RECORD_ROUTE
        size_t prev = -1;
#endif
    };

    size_t N;

    vector<Vertex> vs;

    // n nodes
    Dijkstra(size_t n) : N(n) {
        vs.resize(n);
    }

    void add(size_t from, size_t to, D len) {
        assert(from < N);
        assert(to < N);
        assert(len >= 0);
        vs[from].outs.push_back({ to, len });
    }

    void add_u(size_t a, size_t b, D len) {
        add(a, b, len);
        add(b, a, len);
    }

    D solve(size_t from, size_t to) {
        vs[from].dist = 0;
#ifdef DIJKSTRA_RECORD_ROUTE
        vs[from].prev = from;
#endif

        auto comp = [&](size_t x, size_t y) {
            return vs[x].dist < vs[y].dist || (vs[x].dist == vs[y].dist && x < y);
        };
        set<size_t, decltype(comp)> q { comp };
        for (size_t i = 0; i < N; ++i) {
            q.insert(i);
        }

        while (!q.empty()) {
            size_t i;
            {
                auto it = q.begin();
                i       = *it;
                q.erase(it);
            }

            if (i == to) {
                goto RETURN;
            }

            for (Edge const& e : vs[i].outs) {
                if (vs[e.to].dist > vs[i].dist + e.len) {
                    if (q.find(e.to) != q.end()) {
                        q.erase(e.to);
                        vs[e.to].dist = vs[i].dist + e.len;
#ifdef DIJKSTRA_RECORD_ROUTE
                        vs[e.to].prev = i;
#endif
                        q.insert(e.to);
                    }
                }
            }
        }

RETURN:
        return vs[to].dist;
    }
};
