// https://open.kattis.com/problems/texassummers

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define sqr(x) ((x) * (x))

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

SPFA<3000> spfa;

long x[3000];
long y[3000];

void print(int from, int to) {
    if (spfa.route[to] != from) {
        print(from, spfa.route[to]);
        cout << spfa.route[to] << endl;
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
            spfa.add(i, j, sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
        }
    }

    spfa.solve(n - 2, n - 1);

    if (spfa.route[n - 1] == n - 2) {
        cout << '-' << endl;
    } else {
        print(n - 2, n - 1);
    }

    return 0;
}
