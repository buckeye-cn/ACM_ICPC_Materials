// https://open.kattis.com/problems/walkway

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

Dijkstra<1200> dijk[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 0; true; ++i) {
        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        for (int j = 0; j < n; ++j) {
            int a, b, h;
            cin >> a >> b >> h;

            dijk[i].add(a, b, (a + b) * h);
            dijk[i].add(b, a, (a + b) * h);
        }

        int from, to;
        cin >> from >> to;

        printf("%.2f\n", dijk[i].solve(from, to) * 0.01);
    }
}
