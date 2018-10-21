// https://open.kattis.com/problems/transportation

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

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

EdmondsKarp<3002> ek;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int s, r, f, t;
    cin >> s >> r >> f >> t;

    unordered_map<string, int> v;

    for (int i = 0; i < r; ++i) {
        string s;
        cin >> s;

        v.insert({s, i});
        ek.add(3000, i, 1);
    }

    for (int i = r; i < r + f; ++i) {
        string s;
        cin >> s;

        v.insert({s, i});
        ek.add(i, 3001, 1);
    }

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;

            if (v.find(s) == v.end()) {
                v.insert({s, v.size()});
            }

            int k = v.at(s);

            ek.add(k, 1000 + i, 1);
            ek.add(2000 + i, k, 1);
        }

        ek.add(1000 + i, 2000 + i, 1);
    }

    cout << ek.solve(3000, 3001) << endl;

    return 0;
}
