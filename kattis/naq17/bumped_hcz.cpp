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
vector<pair<long, long>> edge[120000];
long dist[120000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> f >> s >> t;

    for (long i = 0; i < m; ++i) {
        long a, b, c;
        cin >> a >> b >> c;

        edge[a].push_back(pair<long, long> {b, c});
        edge[b].push_back(pair<long, long> {a, c});
        edge[a + n].push_back(pair<long, long> {b + n, c});
        edge[b + n].push_back(pair<long, long> {a + n, c});
    }

    for (long i = 0; i < f; ++i) {
        long a, b;
        cin >> a >> b;

        edge[a].push_back(pair<long, long> {b + n, 0});
    }

    // dijkstra

    struct comp {
        bool operator()(long x, long y) {
            return dist[x] < dist[y] || (dist[x] == dist[y] && x < y);
        }
    };

    set<long, comp> q;

    for (long i = 0; i < n * 2; ++i) {
        dist[i] = 1l << 60;
        q.insert(i);
    }

    q.erase(s);
    dist[s] = 0;
    q.insert(s);

    while (!q.empty()) {
        long i_min = *q.begin();

        q.erase(i_min);
        if (i_min == t || i_min == t + n) break;

        for (pair<long, long> p: edge[i_min]) {
            long alt = dist[i_min] + p.second;

            if (dist[p.first] > alt) {
                if (q.find(p.first) != q.end()) {
                    q.erase(p.first);
                    dist[p.first] = alt;
                    q.insert(p.first);
                }
            }
        }
    }

    cout << min(dist[t], dist[t + n]) << endl;

    return 0;
}
