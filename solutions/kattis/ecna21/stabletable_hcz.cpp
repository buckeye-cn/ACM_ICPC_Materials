// https://open.kattis.com/problems/stabletable

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

SPFA<10000> spfa[2];

int grid[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int h, w;
    cin >> h >> w;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int j = 0; j < w; ++j) {
        spfa[0].add(0, grid[h - 1][j], 1);
        spfa[1].add(grid[h - 1][j], 0, 1);
    }

    for (int i = 1; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (grid[i - 1][j] == grid[i][j]) continue;

            spfa[0].add(grid[i][j], grid[i - 1][j], 1);
            spfa[1].add(grid[i - 1][j], grid[i][j], 1);
        }
    }

    long best = spfa[0].solve(0, grid[0][0]);

    for (int j = 1; j < w; ++j) {
        if (grid[0][0] == grid[0][j]) continue;

        spfa[1].solve(grid[0][0], 0);

        for (int i = 1; i < 10000; ++i) {
            spfa[0].dist[i] += spfa[1].dist[i];
        }

        best += spfa[1].solve(grid[0][j], 0);

        for (int i = 1; i < 10000; ++i) {
            best = min(best, spfa[0].dist[i] + spfa[1].dist[i]);
        }

        break;
    }

    cout << best << endl;

    return 0;
}
