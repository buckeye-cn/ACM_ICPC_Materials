// https://open.kattis.com/problems/bumped

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
struct SPFA {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        edges.push_back({to, len});
        outs[from].push_back(edges.size() - 1);
    }

    long dist[N];
    long route[N];
    long visiting[N];
    bool active[N];

    long solve(long from, long to) {
        memset(active, 0, sizeof(active));

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

                if (dist[e.to] > dist[i] + e.len) {
                    dist[e.to] = dist[i] + e.len;
                    route[e.to] = i;

                    if (!active[e.to]) {
                        visiting[(tail++) % N] = e.to;
                        active[e.to] = true;
                    }
                }
            }
        }

        return dist[to];
    }
};

SPFA<120000> spfa;

long n, m, f, s, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> f >> s >> t;

    for (long i = 0; i < m; ++i) {
        long a, b, c;
        cin >> a >> b >> c;

        spfa.add(a, b, c);
        spfa.add(b, a, c);
        spfa.add(a + n, b + n, c);
        spfa.add(b + n, a + n, c);
    }

    for (long i = 0; i < f; ++i) {
        long a, b;
        cin >> a >> b;

        spfa.add(a, b + n, 0);
    }

    spfa.add(t, t + n, 0);

    cout << spfa.solve(s, t + n) << endl;

    return 0;
}
