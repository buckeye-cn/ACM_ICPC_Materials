template <long N>
struct Prim {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        if (len >= 0) {
            edges.push_back({to, len});
            outs[from].push_back(edges.size() - 1);
            edges.push_back({from, len});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long dist[N];
    long route[N];

    long solve() {
        auto comp = [&](long x, long y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        };

        set<long, decltype(comp)> q {comp};

        for (long i = 0; i < N; ++i) {
            dist[i] = 1l << 60;
            q.insert(i);
        }

        while (!q.empty()) {
            long i = *q.begin();
            q.erase(i);

            if (dist[i] == 1l << 60) {
                dist[i] = 0;
            }

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

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

        long result = 0;

        for (long i = 0; i < N; ++i) {
            result += dist[i];
        }

        return result;
    }
};
