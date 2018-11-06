template <long N>
struct EdmondsKarp {
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

    long amount[N];
    long route[N];
    long visiting[N];

    long solve(long from, long to) {
        long flow = 0;

        while (true) {
            memset(amount, 0, sizeof(amount));

            long head = 0;
            long tail = 0;

            amount[from] = 1l << 60;
            visiting[tail++] = from;

            while (head < tail && !amount[to]) {
                long i = visiting[head++];

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap) {
                        amount[e.to] = min(amount[i], e.cap);
                        route[e.to] = outs[i][j];

                        visiting[tail++] = e.to;
                    }
                }
            }

            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from) {
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};
