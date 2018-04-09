// https://open.kattis.com/problems/dotsboxes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int n;
bool ud[100][100];
bool lr[100][100];
int slot[100][100];

template <long N>
struct EdmondsKarp {
    struct Edge {
        long from, to, cap;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long cap){
        if (cap > 0) {
            edges.push_back(Edge {from, to, cap});
            outs[from].push_back(edges.size() - 1);
            edges.push_back(Edge {to, from, 0});
            outs[to].push_back(edges.size() - 1);
        }
    }

    long amount[N];
    long route[N];

    long solve(long from, long to){
        long flow = 0;

        while (true) {
            queue<long> q;

            memset(amount, 0, sizeof(amount));

            q.push(from);

            amount[from] = 1l << 60;
            while (!q.empty() && !amount[to]){
                long i = q.front();
                q.pop();

                for (long j = 0; j < outs[i].size(); ++j){
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap){
                        amount[e.to] = min(amount[i], e.cap);
                        route[e.to] = outs[i][j];

                        q.push(e.to);
                    }
                }
            }
            if (!amount[to]) break;

            for (long i = to; i != from; i = edges[route[i]].from){
                edges[route[i]].cap -= amount[to];
                edges[route[i] ^ 1].cap += amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};

EdmondsKarp<10000> ek;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 1; i <= n; ++i) {
        char c;

        for (int j = 1; j <= n; ++j) {
            cin >> c;

            if (j == n) break;

            cin >> c;
            ud[i][j] = c == '-';
        }

        if (i == n) break;

        for (int j = 1; j <= n; ++j) {
            cin >> c;
            lr[i][j] = c == '|';

            if (j == n) break;

            cin >> c;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            slot[i][j] = !ud[i][j] + !ud[i + 1][j] + !lr[i][j] + !lr[i][j + 1] - 1;

            if ((i ^ j) & 1) {
                ek.add(100 * i + j, 9999, slot[i][j]);
            } else {
                ek.add(9998, 100 * i + j, slot[i][j]);
            }

            // cout << slot[i][j] << ' ';
        }

        // cout << endl;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j == n) break;

            if (!ud[i][j]) {
                if ((i ^ j) & 1) {
                    ek.add(100 * (i - 1) + j, 100 * i + j, 1);
                } else {
                    ek.add(100 * i + j, 100 * (i - 1) + j, 1);
                }
            }
        }

        if (i == n) break;

        for (int j = 1; j <= n; ++j) {
            if (!lr[i][j]) {
                if ((i ^ j) & 1) {
                    ek.add(100 * i + (j - 1), 100 * i + j, 1);
                } else {
                    ek.add(100 * i + j, 100 * i + (j - 1), 1);
                }
            }
        }
    }

    cout << ek.solve(9998, 9999) + 1 << endl;

    return 0;
}
