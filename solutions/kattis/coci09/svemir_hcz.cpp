// https://open.kattis.com/problems/svemir

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

Prim<100000> prim;

set<pair<int, int>> xset;
set<pair<int, int>> yset;
set<pair<int, int>> zset;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;

        xset.insert({x, i});
        yset.insert({y, i});
        zset.insert({z, i});
    }

    pair<int, int> last;

    last = *xset.begin();
    for (pair<int, int> p: xset) {
        prim.add(last.second, p.second, p.first - last.first);
        last = p;
    }

    last = *yset.begin();
    for (pair<int, int> p: yset) {
        prim.add(last.second, p.second, p.first - last.first);
        last = p;
    }

    last = *zset.begin();
    for (pair<int, int> p: zset) {
        prim.add(last.second, p.second, p.first - last.first);
        last = p;
    }

    cout << prim.solve() << endl;

    return 0;
}
