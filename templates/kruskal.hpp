#include <algorithm>
#include <cassert>
#include <cstdint>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// (u)int64, float
template <typename D>
struct Kruskal {
    static constexpr D Inf = 1l << 60;

    struct Edge {
        size_t n1, n2;
        D len;

        bool operator<(Edge const& o) const noexcept {
            return len < o.len || (len == o.len && (n1 < o.n1 || (n1 == o.n1 && (n2 < o.n2))));
        }
    };

    typedef unordered_map<size_t, vector<Edge>> Forest;

    size_t N;
    vector<Edge> edges;

    // n nodes
    Kruskal(size_t n) : N(n) {}

    void add(size_t n1, size_t n2, D len) {
        assert(n1 < N);
        assert(n2 < N);
        assert(len >= 0);
        if (n1 > n2) swap(n1, n2);
        edges.push_back({ n1, n2, len });
    }

    void solve(Forest& forest) {
        sort(edges.begin(), edges.end());

        vector<size_t> _ufs(N);
        for (size_t i = 0; i < N; i++)
            _ufs[i] = i;

        auto ufs_p = [&](size_t i) -> size_t* {
            auto p = i;
            while (_ufs[p] != p)
                p = _ufs[p];
            _ufs[i] = p;
            return &_ufs[i];
        };

        for (Edge const& e : edges) {
            auto* ufs_n1p = ufs_p(e.n1);
            auto* ufs_n2p = ufs_p(e.n2);
            if (*ufs_n1p != *ufs_n2p) {
                if (*ufs_n1p > *ufs_n2p)
                    swap(*ufs_n1p, *ufs_n2p);

                auto it = forest.find(*ufs_n2p);
                if (it != forest.end()) {
                    forest[*ufs_n1p].insert(forest[*ufs_n1p].end(), it->second.begin(), it->second.end());
                    forest.erase(it);
                }

                forest[*ufs_n1p].push_back(e);

                *ufs_n2p = *ufs_n1p;
            }
        }

        return;
    }
};
