template <long N>
struct Tarjan {
    vector<long> outs[N];

    void add(long from, long to) {
        outs[from].push_back(to);
    }

    long t_self[N];
    long t_low[N];

    vector<long> s;
    bool visiting[N];

    long now;
    long now_scc;

    void dfs(long (&scc)[N], long from) {
        t_self[from] = now;
        t_low[from] = now;
        now += 1;

        visiting[from] = true;
        s.push_back(from);

        for (long j = 0; j < outs[from].size(); ++j) {
            long to = outs[from][j];

            if (!t_self[to]) {
                dfs(scc, to);

                t_low[from] = min(t_low[from], t_low[to]);
            } else if (visiting[to]) {
                t_low[from] = min(t_low[from], t_self[to]);
            }
        }

        if (t_low[from] == t_self[from]) {
            while (true) {
                long to = s.back();
                s.pop_back();

                visiting[to] = false;
                scc[to] = now_scc;

                if (to == from) {
                    break;
                }
            }

            now_scc += 1;
        }
    }

    void solve(long (&scc)[N]) {
        memset(t_self, 0, sizeof(t_self));
        memset(visiting, 0, sizeof(visiting));

        now = 1;
        now_scc = 0;

        for (long i = 0; i < N; ++i) {
            if (!t_self[i]) {
                dfs(scc, i);
            }
        }
    }
};
