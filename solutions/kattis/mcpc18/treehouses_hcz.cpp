// https://open.kattis.com/problems/treehouses

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
struct Prim {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        edges.push_back({to, len});
        outs[from].push_back(edges.size() - 1);
        edges.push_back({from, len});
        outs[to].push_back(edges.size() - 1);
    }

    long dist[N];
    long route[N];

    long solve() {
        set<pair<long, long>> q;

        for (long i = 0; i < N; ++i) {
            dist[i] = 1l << 60;
            q.insert({dist[i], i});
        }

        while (!q.empty()) {
            pair<long, long> i = *q.begin();
            q.erase(i);

            if (i.first == 1l << 60) {
                dist[i.second] = 0;
            }

            for (long j = 0; j < outs[i.second].size(); ++j) {
                Edge &e = edges[outs[i.second][j]];

                if (dist[e.to] > e.len) {
                    if (q.find({dist[e.to], e.to}) != q.end()) {
                        q.erase({dist[e.to], e.to});
                        dist[e.to] = e.len;
                        route[e.to] = i.second;
                        q.insert({dist[e.to], e.to});
                    }
                }
            }
        }

        long result = 0;

        for (long i = 0; i < N; ++i) {
            result += dist[i];
        }

        return result;
    }
};

Prim<1000> prim;

double pos_x[1000];
double pos_y[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, e, p;
    cin >> n >> e >> p;

    for (int i = 0; i < n; ++i) {
        cin >> pos_x[i] >> pos_y[i];

        if (i < e - 1) {
            prim.add(i, i + 1, 0);
        }

        for (int j = 0; j < i; ++j) {
            prim.add(i, j, long(1e6 * sqrt(sqr(pos_x[i] - pos_x[j]) + sqr(pos_y[i] - pos_y[j]))));
        }
    }

    for (int i = 0; i < p; ++i) {
        int a, b;
        cin >> a >> b;

        prim.add(a - 1, b - 1, 0);
    }

    cout << 1e-6 * prim.solve() << endl;

    return 0;
}
