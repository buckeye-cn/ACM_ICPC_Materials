#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

template <long N>
struct EdmondsKarp {
    struct Edge {
        long from, to, cap;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap){
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0});
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

                    if (!amount[e.to] && e.cap){
                        amount[e.to] = min(amount[i], e.cap);
                        route[e.to] = outs[i][j];

                        q.push(e.to);
                    }
                }
            }
            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from){
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};

int value[120][120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> value[i][j];
            }
        }

        int result = 0;

        for (int v = -n; v <= n; ++v) {
            if (!v) continue;

            EdmondsKarp<202> ek;

            for (int i = 0; i < n; ++i) {
                ek.add(200, i, 1);
                ek.add(i + 100, 201, 1);
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (value[i][j] == v) {
                        ek.add(i, j + 100, 1);
                    }
                }
            }

            result += ek.solve(200, 201);
        }

        cout << n * n - result << endl;
    }

    return 0;
}
