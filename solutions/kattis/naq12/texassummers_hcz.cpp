// https://open.kattis.com/problems/texassummers

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>

#define sqr(x) ((x) * (x))

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

Dijkstra<3000> dijk;

long x[3000];
long y[3000];

void print(int from, int to) {
    if (dijk.route[to] != from) {
        print(from, dijk.route[to]);
        cout << dijk.route[to] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    n += 2;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dijk.add(i, j, sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
        }
    }

    dijk.solve(n - 2, n - 1);

    if (dijk.route[n - 1] == n - 2) {
        cout << '-' << endl;
    } else {
        print(n - 2, n - 1);
    }

    return 0;
}
