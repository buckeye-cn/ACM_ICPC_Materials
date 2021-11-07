// https://open.kattis.com/problems/dragonball1

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

template <long N>
struct Dijkstra {
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

    long solve(long from, long to) {
        set<pair<long, long>> q;

        for (long i = 0; i < N; ++i) {
            if (i == from) {
                dist[i] = 0;
            } else {
                dist[i] = 1l << 60;
            }
            q.insert({dist[i], i});
        }

        while (!q.empty()) {
            pair<long, long> i = *q.begin();
            q.erase(i);

            if (i.second == to) {
                return i.first;
            }

            for (long j = 0; j < outs[i.second].size(); ++j) {
                Edge &e = edges[outs[i.second][j]];

                if (dist[e.to] > i.first + e.len) {
                    if (q.find({dist[e.to], e.to}) != q.end()) {
                        q.erase({dist[e.to], e.to});
                        dist[e.to] = i.first + e.len;
                        route[e.to] = i.second;
                        q.insert({dist[e.to], e.to});
                    }
                }
            }
        }

        return 1l << 60;
    }
};

Dijkstra<200000> dijk;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b, t;
        cin >> a >> b >> t;

        dijk.add(a - 1, b - 1, t);
        dijk.add(b - 1, a - 1, t);
    }

    int c[7];

    for (int i = 0; i < 7; ++i) {
        cin >> c[i];
    }

    int d[7][7];

    for (int i = 0; i < 7; ++i) {
        for (int j = i + 1; j < 7; ++j) {
            d[i][j] = dijk.solve(c[i] - 1, c[j] - 1);
            d[j][i] = d[i][j];
        }
    }

    long best = 2.1e9;

    for (int i = 0; i < 7; ++i) {
        long l1 = dijk.solve(0, c[i] - 1);

        for (int j = 0; j < 7; ++j) {
            if (i == j) continue;

            long l2 = l1 + d[i][j];

            for (int k = 0; k < 7; ++k) {
                if (i == k || j == k) continue;

                long l3 = l2 + d[j][k];

                for (int s = 0; s < 7; ++s) {
                    if (i == s || j == s || k == s) continue;

                    long l4 = l3 + d[k][s];

                    for (int t = 0; t < 7; ++t) {
                        if (i == t || j == t || k == t || s == t) continue;

                        long l5 = l4 + d[s][t];

                        for (int r = 0; r < 7; ++r) {
                            if (i == r || j == r || k == r || s == r || t == r) continue;

                            long l6 = l5 + d[t][r];

                            for (int a = 0; a < 7; ++a) {
                                if (i == a || j == a || k == a || s == a || t == a || r == a) continue;

                                long l7 = l6 + d[r][a];

                                best = min(best, l7);
                            }
                        }
                    }
                }
            }
        }
    }

    if (best == 2.1e9) {
        cout << -1 << endl;
    } else {
        cout << best << endl;
    }

    return 0;
}
