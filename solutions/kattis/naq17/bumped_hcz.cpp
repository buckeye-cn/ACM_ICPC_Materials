// https://open.kattis.com/problems/bumped

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
        if (len >= 0) {
            edges.push_back({to, len});
            outs[from].push_back(edges.size() - 1);
        }
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

        return -1;
    }
};

Dijkstra<120000> dijk;

long n, m, f, s, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> f >> s >> t;

    for (long i = 0; i < m; ++i) {
        long a, b, c;
        cin >> a >> b >> c;

        dijk.add(a, b, c);
        dijk.add(b, a, c);
        dijk.add(a + n, b + n, c);
        dijk.add(b + n, a + n, c);
    }

    for (long i = 0; i < f; ++i) {
        long a, b;
        cin >> a >> b;

        dijk.add(a, b + n, 0);
    }

    dijk.add(t, t + n, 0);

    cout << dijk.solve(s, t + n) << endl;

    return 0;
}
