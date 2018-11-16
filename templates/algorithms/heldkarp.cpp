// Travelling Salesman Problem

template <long N>
struct HeldKarp {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        if (len >= 0) {
            edges.push_back({to, len});
            outs[from].push_back(edges.size() - 1);
        }
    }

    long dist[N][N];
    long best[1l << (N - 1)][N];

    long solve(long n) {
        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < n; ++j) {
                dist[i][j] = 1l << 60;
            }

            dist[i][i] = 0;

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

                dist[i][e.to] = min(dist[i][e.to], e.len);
            }
        }

        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < n; ++j) {
                for (long k = 0; k < n; ++k) {
                    dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
            }
        }

        for (long i = 0; i < (1l << (n - 1)); ++i) {
            for (long j = 0; j < n; ++j) {
                best[i][j] = 1l << 60;
            }

            for (long j = 0; j < n - 1; ++j) {
                if (i == 1l << j) {
                    best[i][j] = dist[n - 1][j];
                } else if (i & (1l << j)) {
                    for (long k = 0; k < n - 1; ++k) {
                        if ((i ^ (1l << j)) & (1l << k)) {
                            best[i][j] = min(best[i][j], dist[j][k] + best[i ^ (1l << j)][k]);
                        }
                    }
                }
            }
        }

        long result = 1l << 60;
        for (long i = 0; i < n - 1; ++i) {
            result = min(result, dist[i][n - 1] + best[(1l << (n - 1)) - 1][i]);
        }

        return result;
    }
};
