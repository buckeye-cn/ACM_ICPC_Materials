// Minimum Spanning Tree

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
        set<pair<long, long>> q;

        for (long i = 0; i < N; ++i) {
            dist[i] = 1l << 60;
            q.insert({dist[i], i});
        }

        while (!q.empty()) {
            pair<long, long> i = *q.begin();
            q.erase(i);

            if (i.first == 1l << 60) {
                dist[i.second] = 0;
            }

            for (long j = 0; j < outs[i.second].size(); ++j) {
                Edge &e = edges[outs[i.second][j]];

                if (dist[e.to] > e.len) {
                    if (q.find({dist[e.to], e.to}) != q.end()) {
                        q.erase({dist[e.to], e.to});
                        dist[e.to] = e.len;
                        route[e.to] = i.second;
                        q.insert({dist[e.to], e.to});
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
