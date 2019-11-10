// https://open.kattis.com/problems/biotrip

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

SPFA<40000> spfa;

int m[1000];
int dx[1000][20];
int tx[1000][20];
int amap[1000][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, d, a1, a2;
    cin >> n >> d >> a1 >> a2;
    d -= 1;

    for (int i = 0; i < n; ++i) {
        cin >> m[i];

        for (int j = 0; j < m[i]; ++j) {
            cin >> dx[i][j] >> tx[i][j];
            dx[i][j] -= 1;

            cin >> amap[i][dx[i][j]];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m[i]; ++j) {
            int k = dx[i][j];

            for (int l = 0; l < m[k]; ++l) {
                int delta_a = amap[k][dx[k][l]] - amap[k][i];

                if (
                    !k
                    || (delta_a >= -180 - a2 && delta_a <= -180 + a1)
                    || (delta_a >= 180 - a2 && delta_a <= 180 + a1)
                ) {
                    spfa.add(i * 20 + j, k * 20 + l, tx[i][j]);
                    spfa.add(20000 + i * 20 + j, 20000 + k * 20 + l, tx[i][j]);
                }
            }
        }
    }

    for (int a = 0; a < 20; ++a) {
        spfa.add(0, a, 0);
        spfa.add(d * 20 + a, 20000 + d * 20 + a, 0);
    }

    long len = spfa.solve(0, 20000);

    if (len < 1l << 60) {
        cout << len << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
