// https://open.kattis.com/problems/railway

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

bool is_c[100001];
SPFA<300001> spfa;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        char ax, bx;
        cin >> a >> ax >> b >> bx;

        if (ax == 'A') {
            if (a == 1) {
                spfa.add(0, b + 100000 * (bx - 'A'), 1);
            } else {
                spfa.add(a + 100000, b + 100000 * (bx - 'A'), 1);
                spfa.add(a + 200000, b + 100000 * (bx - 'A'), 1);
            }
        } else {
            spfa.add(a, b + 100000 * (bx - 'A'), 1);
        }

        if (bx == 'A') {
            if (b == 1) {
                spfa.add(0, a + 100000 * (ax - 'A'), 1);
            } else {
                spfa.add(b + 100000, a + 100000 * (ax - 'A'), 1);
                spfa.add(b + 200000, a + 100000 * (ax - 'A'), 1);
            }
        } else {
            spfa.add(b, a + 100000 * (ax - 'A'), 1);
        }
    }

    spfa.solve(0, 0);

    if (spfa.dist[100001] == 1l << 60 && spfa.dist[200001] == 1l << 60) {
        cout << "Impossible" << endl;
    } else {
        int p = spfa.dist[100001] < spfa.dist[200001] ? 100001 : 200001;

        while (p) {
            if (p >= 200001) {
                is_c[p - 200000] = true;
            }

            p = spfa.route[p];
        }

        for (int i = 1; i <= n; ++i) {
            cout << (is_c[i] ? 'C' : 'B');
        }

        cout << endl;
    }

    return 0;
}
