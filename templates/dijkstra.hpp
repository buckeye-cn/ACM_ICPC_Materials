#include <cassert>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

template<typename D>
struct Dijkstra {
    static constexpr D Inf = 1l << 60;

    struct Edge {
        size_t to;
        D len;
    };

    size_t N;

    vector<vector<Edge>> edges;

    Dijkstra(size_t n) : N(n) {
        edges.resize(n);
    }

    void add(size_t from, size_t to, D len) {
        assert(len >= 0);
        edges[from].push_back({ to, len });
    }

    void add_u(size_t a, size_t b, D len) {
        add(a, b, len);
        add(b, a, len);
    }

#ifdef DIJKSTRA_RECORD_ROUTE
    tuple<D, vector<size_t>>
#else
    D
#endif
    solve(size_t from, size_t to) {
        vector<D> dist(N);

#ifdef DIJKSTRA_RECORD_ROUTE
        vector<size_t> route(N);
#endif

        auto comp = [&](size_t x, size_t y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        };

        set<size_t, decltype(comp)> q { comp };

        for (size_t i = 0; i < N; ++i) {
            dist[i] = i == from ? 0 : Inf;
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

            for (Edge const& e : edges[i]) {
                if (dist[e.to] > dist[i] + e.len) {
                    auto it = q.find(e.to);
                    if (it != q.end()) {
                        q.erase(it);
                        dist[e.to] = dist[i] + e.len;
#ifdef DIJKSTRA_RECORD_ROUTE
                        route[e.to] = i;
#endif
                        q.insert(e.to);
                    }
                }
            }
        }

RETURN:
#ifdef DIJKSTRA_RECORD_ROUTE
        return make_tuple(dist[to], route);
#else
        return dist[to];
#endif
    }
};
