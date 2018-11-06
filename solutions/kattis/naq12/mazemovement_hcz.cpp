// https://open.kattis.com/problems/mazemovement

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
struct EdmondsKarp {
    struct Edge {
        long from, to, cap;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap) {
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long amount[N];
    long route[N];
    long visiting[N];

    long solve(long from, long to) {
        long flow = 0;

        while (true) {
            memset(amount, 0, sizeof(amount));

            long head = 0;
            long tail = 0;

            amount[from] = 1l << 60;
            visiting[tail++] = from;

            while (head < tail && !amount[to]) {
                long i = visiting[head++];

                for (long j = 0; j < outs[i].size(); ++j) {
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap) {
                        amount[e.to] = min(amount[i], e.cap);
                        route[e.to] = outs[i][j];

                        visiting[tail++] = e.to;
                    }
                }
            }

            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from) {
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};

EdmondsKarp<1000> ek;

int gcd(int y, int x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int room[1000];
int lo;
int hi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> room[i];

        if (room[lo] > room[i]) {
            lo = i;
        }

        if (room[hi] < room[i]) {
            hi = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int cap = gcd(room[i], room[j]);

            if (cap > 1) {
                ek.add(i, j, cap);
                ek.add(j, i, cap);
            }
        }
    }

    cout << ek.solve(lo, hi) << endl;

    return 0;
}
