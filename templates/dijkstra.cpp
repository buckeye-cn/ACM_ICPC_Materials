template <long N>
struct Dijkstra {
    struct Edge {
        long from, to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        if (len >= 0) {
            edges.push_back({from, to, len});
            outs[from].push_back(edges.size() - 1);
        }
    }

    long dist[N];

    long solve(long from, long to) {
        auto comp = [&](long x, long y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        };

        set<long, decltype(comp)> q {comp};

        for (long i = 0; i < N; ++i) {
            if (i == from) {
                dist[i] = 0;
            } else {
                dist[i] = 1l << 60;
            }
            q.insert(i);
        }

        while (!q.empty()) {
            long i = *q.begin();
            q.erase(i);

            if (i == to) {
                return dist[i];
            }

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

                long alt = dist[i] + e.len;

                if (dist[e.to] > alt) {
                    if (q.find(e.to) != q.end()) {
                        q.erase(e.to);
                        dist[e.to] = alt;
                        q.insert(e.to);
                    }
                }
            }
        }

        return -1;
    }
};
