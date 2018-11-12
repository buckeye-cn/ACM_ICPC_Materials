// https://open.kattis.com/problems/eulerianpath

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

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

HierholzerDirected<10000> hier;

int out_tot[10000];
int in_tot[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 0; true; ++i) {
        memset(out_tot, 0, sizeof(out_tot));
        memset(in_tot, 0, sizeof(in_tot));

        int n, m;
        cin >> n >> m;

        if (!n) {
            return 0;
        }

        for (int j = 0; j < m; ++j) {
            int from, to;
            cin >> from >> to;

            out_tot[from] += 1;
            in_tot[to] += 1;
            hier.add(from, to);
        }

        bool ok = true;
        int from = -1;
        int to = -1;
        for (int j = 0; j < n; ++j) {
            if (out_tot[j] == in_tot[j]) {
                // nothing
            } else if (from == -1 && out_tot[j] == in_tot[j] + 1) {
                from = j;
            } else if (to == -1 && out_tot[j] + 1 == in_tot[j]) {
                to = j;
            } else {
                ok = false;
            }
        }

        if (from == -1) {
            from = 0;
            to = 0;
        }

        if (ok) {
            vector<long> result;

            hier.solve(result, from);

            if (result.size() == m + 1) {
                for (int j = m; j > 0; --j) {
                    cout << result[j] << ' ';
                }

                cout << result[0] << endl;
            } else {
                cout << "Impossible" << endl;
            }
        } else {
            cout << "Impossible" << endl;
        }

        hier.edges.clear();
        for (int j = 0; j < n; ++j) {
            hier.outs[j].clear();
        }
    }
}
