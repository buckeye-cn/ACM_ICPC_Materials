// Maximum Flow

template <long N>
struct Dinic {
    struct Edge {
        long from, to, cap;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap) {
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long layer[N];
    long visiting[N];
    long step[N];

    long dfs(long from, long to, long limit) {
        if (from == to) {
            return limit;
        }

        long amount = limit;

        for (long j = step[from]; j < outs[from].size(); ++j) {
            Edge &e = edges[outs[from][j]];

            if (layer[e.to] == layer[from] + 1 && e.cap) {
                long flow = dfs(e.to, to, min(amount, e.cap));

                if (flow) {
                    e.cap -= flow;
                    edges[outs[from][j] ^ 1].cap += flow;
                    amount -= flow;

                    if (!amount) {
                        step[from] = j;

                        return limit;
                    }
                }
            }
        }

        step[from] = outs[from].size();

        return limit - amount;
    }

    long solve(long from, long to) {
        long flow = 0;

        while (true) {
            memset(layer, 0, sizeof(layer));
            memset(step, 0, sizeof(step));

            long head = 0;
            long tail = 0;

            layer[from] = 1;
            visiting[tail++] = from;

            while (head < tail && !layer[to]) {
                long i = visiting[head++];

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (!layer[e.to] && e.cap) {
                        layer[e.to] = layer[i] + 1;

                        visiting[tail++] = e.to;
                    }
                }
            }

            if (!layer[to]) break;

            flow += dfs(from, to, 1l << 60);
        }

        return flow;
    }
};

template <long N>
struct DinicMinCost {
    struct Edge {
        long from, to, cap, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap, long len) {
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap, len});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0, -len});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long dist[N];
    long visiting[N];
    bool active[N];
    long step[N];

    long dfs(long from, long to, long limit, long &cost) {
        if (from == to) {
            return limit;
        }

        active[from] = true;

        long amount = limit;

        for (long j = step[from]; j < outs[from].size(); ++j) {
            Edge &e = edges[outs[from][j]];

            if (dist[e.to] == dist[from] + e.len && e.cap && !active[e.to]) {
                long flow = dfs(e.to, to, min(amount, e.cap), cost);

                if (flow) {
                    e.cap -= flow;
                    edges[outs[from][j] ^ 1].cap += flow;
                    amount -= flow;
                    cost += flow * e.len;

                    if (!amount) {
                        step[from] = j;

                        return limit;
                    }
                }
            }
        }

        active[from] = false;
        step[from] = outs[from].size();

        return limit - amount;
    }

    pair<long, long> solve(long from, long to) {
        long flow = 0;
        long cost = 0;

        while (true) {
            memset(active, 0, sizeof(active));
            memset(step, 0, sizeof(step));

            for (int i = 0; i < N; ++i) {
                dist[i] = 1l << 60;
            }

            long head = 0;
            long tail = 0;

            dist[from] = 0;
            visiting[(tail++) % N] = from;
            active[from] = true;

            while (head < tail) {
                long i = visiting[(head++) % N];
                active[i] = false;

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (e.cap && dist[e.to] > dist[i] + e.len) {
                        dist[e.to] = dist[i] + e.len;

                        if (!active[e.to]) {
                            visiting[(tail++) % N] = e.to;
                            active[e.to] = true;
                        }
                    }
                }
            }

            if (dist[to] == 1l << 60) break;

            flow += dfs(from, to, 1l << 60, cost);
        }

        return {flow, cost};
    }
};
