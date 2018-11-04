#include <bits/stdc++.h>

using namespace std;

#define D int64_t
struct Prim {
    static constexpr D Inf = 1l << 60;

    struct Edge { size_t to; D len; };
    struct Vertex {
        vector<Edge> outs;
        D node = Inf;
        D dist = Inf;
        size_t prev = -1;
    };

    size_t N;

    vector<Vertex> vs;

    // n nodes
    Prim(size_t n) : N(n) {
        vs.resize(n);
    }

    void add(size_t from, size_t to, D len) {
        vs[from].outs.push_back({to, len});
    }

    void add_u(size_t a, size_t b, D len) {
        add(a, b, len);
        add(b, a, len);
    }

    D solve(size_t from) {
        vs[from].node = 0;
        vs[from].dist = 0;
        vs[from].prev = from;

        auto comp = [&](size_t x, size_t y) {
            return vs[x].node < vs[y].node || (vs[x].node == vs[y].node && x < y);
        };

        set<size_t, decltype(comp)> q {comp};

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

            for (Edge const& e : vs[i].outs) {
                if (vs[e.to].node > vs[i].node + 1 || (vs[e.to].node == vs[i].node + 1 && vs[e.to].dist > e.len)) {
                    if (q.find(e.to) != q.end()) {
                        q.erase(e.to);
                        vs[e.to].node = vs[i].node + 1;
                        vs[e.to].dist = e.len;
                        vs[e.to].prev = i;
                        q.insert(e.to);
                    }
                }
            }
        }

        D result = 0;

        for (size_t i = 0; i < N; ++i) {
            if (vs[i].dist == Inf)
                return Inf;
            result += vs[i].dist;
        }

        return result;
    }
};

unordered_map<string, int> L2I;

int64_t COST[103][103];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int N_LANG, N_TRANS;
    cin >> N_LANG >> N_TRANS;

    L2I["English"] = 0;
    for (int i = 1; i <= N_LANG; i++) {
        string l;
        cin >> l;
        L2I[l] = i;
    }

    Prim pr(N_LANG+1);

    for (int i = 0; i < N_TRANS; i++) {
        string l1, l2;
        int cost;
        cin >> l1 >> l2 >> cost;
        pr.add_u(L2I[l1], L2I[l2], cost);
        COST[L2I[l1]][L2I[l2]] = cost;
        COST[L2I[l2]][L2I[l1]] = cost;
    }

    auto tot = pr.solve(0);
    if (tot < pr.Inf) {
        cout << tot << endl;
    } else {
        cout << "Impossible\n";
    }
}
