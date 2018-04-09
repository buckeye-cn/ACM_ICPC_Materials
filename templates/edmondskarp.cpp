template <long N>
struct EdmondsKarp {
    struct Edge {
        long from, to, cap, flow;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap){
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap, 0});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0, 0});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long amount[N];
    long route[N];

    long solve(long from, long to){
        long flow = 0;

        while (true) {
            queue<long> q;

            memset(amount, 0, sizeof(amount));

            q.push(from);

            amount[from] = 1l << 60;
            while (!q.empty() && !amount[to]){
                long i = q.front();
                q.pop();

                for (long j = 0; j < outs[i].size(); ++j){
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap > e.flow){
                        amount[e.to] = min(amount[i], e.cap - e.flow);
                        route[e.to] = outs[i][j];

                        q.push(e.to);
                    }
                }
            }
            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from){
                edges[route[i]].flow += amount[to];
                edges[route[i] ^ 1].flow -= amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};
