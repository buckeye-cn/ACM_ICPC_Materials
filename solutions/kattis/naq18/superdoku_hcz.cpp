// https://open.kattis.com/problems/superdoku

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

EdmondsKarp<202> ek[100];

int n, k;
int data[100][100];
__int128 mask_i[100];
__int128 mask_j[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> data[i][j];
            data[i][j] -= 1;

            __int128 mask = mask_i[i] | mask_j[j];
            __int128 m = __int128(1) << data[i][j];

            if (!(mask & m)) {
                mask_i[i] ^= m;
                mask_j[j] ^= m;
            } else {
                cout << "no" << endl;

                return 0;
            }
        }
    }

    for (int i = k; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ek[i].add(200, j, 1);
            ek[i].add(100 + j, 201, 1);
        }

        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if ((mask_j[j] & (__int128(1) << k)) == 0) {
                    ek[i].add(j, 100 + k, 1);
                }
            }
        }

        ek[i].solve(200, 201);

        for (auto &edge: ek[i].edges) {
            if (!edge.cap && edge.from < 100 && edge.to < 200) {
                int j = edge.from;
                int k = edge.to - 100;

                data[i][j] = k;
                mask_j[j] ^= __int128(1) << k;
            }
        }
    }

    cout << "yes" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) {
                cout << ' ';
            }
            cout << data[i][j] + 1;
        }
        cout << endl;
    }

    return 0;
}
