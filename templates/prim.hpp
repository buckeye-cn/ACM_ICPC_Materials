#include <cassert>
#include <set>
#include <vector>

using namespace std;

// (u)int64, float
template <typename D>
struct Prim {
    static constexpr D Inf = 1l << 60;

    struct Edge {
        size_t to;
        D len;
    };

    size_t N;

    vector<vector<Edge>> edges;

    // n nodes
    Prim(size_t n) : N(n) {
        edges.resize(n);
    }

    void add(size_t from, size_t to, D len) {
        assert(from < N);
        assert(to < N);
        assert(len >= 0);
        edges[from].push_back({to, len});
    }

    void add_u(size_t a, size_t b, D len) {
        add(a, b, len);
        add(b, a, len);
    }

    vector<size_t> dist;
    vector<size_t> route;

    D solve(size_t from) {
        dist.resize(N);
        route.resize(N);

        auto comp = [&](size_t x, size_t y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        };

        set<size_t, decltype(comp)> q {comp};

        for (size_t i = 0; i < N; ++i) {
            dist[i] = i == from ? 0 : Inf;
            route[i] = -1;
            q.insert(i);
        }

        while (!q.empty()) {
            size_t i;
            {
                auto it = q.begin();
                i       = *it;
                q.erase(it);
            }

            if (dist[i] == Inf) {
                dist[i] = 0;
            }

            for (Edge const& e : edges[i]) {
                if (dist[e.to] > e.len) {
                    if (q.find(e.to) != q.end()) {
                        q.erase(e.to);
                        dist[e.to] = e.len;
                        route[e.to] = i;
                        q.insert(e.to);
                    }
                }
            }
        }

        D result = 0;

        for (size_t i = 0; i < N; ++i) {
            result += dist[i];
        }

        return result;
    }
};
