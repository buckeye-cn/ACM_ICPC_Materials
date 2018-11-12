// Eulerian Circuit

template <long N>
struct HierholzerUndirected {
    struct Edge {
        long to;
        bool chosen;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to) {
        edges.push_back(Edge {to, false});
        outs[from].push_back(edges.size() - 1);
        edges.push_back(Edge {from, false});
        outs[to].push_back(edges.size() - 1);
    }

    long step[N];

    void dfs(vector<long> &path, long from) {
        for (; step[from] < outs[from].size(); ++step[from]) {
            Edge &e = edges[outs[from][step[from]]];

            if (!e.chosen) {
                e.chosen = true;
                edges[outs[from][step[from]] ^ 1].chosen = true;
                dfs(path, e.to);
            }
        }

        path.push_back(from);
    }

    void solve(vector<long> &path, long from) {
        memset(step, 0, sizeof(step));

        dfs(path, from);
    }
};

template <long N>
struct HierholzerDirected {
    struct Edge {
        long to;
        bool chosen;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to) {
        edges.push_back(Edge {to, false});
        outs[from].push_back(edges.size() - 1);
    }

    long step[N];

    void dfs(vector<long> &path, long from) {
        for (; step[from] < outs[from].size(); ++step[from]) {
            Edge &e = edges[outs[from][step[from]]];

            if (!e.chosen) {
                e.chosen = true;
                dfs(path, e.to);
            }
        }

        path.push_back(from);
    }

    void solve(vector<long> &path, long from) {
        memset(step, 0, sizeof(step));

        dfs(path, from);
    }
};
