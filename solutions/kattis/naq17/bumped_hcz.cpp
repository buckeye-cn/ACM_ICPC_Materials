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

long n, m, f, s, t;

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
        auto comp = [&](long x, long y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        };

        set<long, decltype(comp)> q {comp};

        for (long i = 0; i < N; ++i) {
            if (i == from) {
                dist[i] = 0;
            } else {
                dist[i] = 1l << 60;
            }
            q.insert(i);
        }

        while (!q.empty()) {
            long i = *q.begin();
            q.erase(i);

            if (i == to) {
                return dist[i];
            }

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

                if (dist[e.to] > dist[i] + e.len) {
                    if (q.find(e.to) != q.end()) {
                        q.erase(e.to);
                        dist[e.to] = dist[i] + e.len;
                        route[e.to] = i;
                        q.insert(e.to);
                    }
                }
            }
        }

        return -1;
    }
};

Dijkstra<120000> dijk;

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
