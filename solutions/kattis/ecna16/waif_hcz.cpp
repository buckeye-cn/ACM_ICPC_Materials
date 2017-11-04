// https://open.kattis.com/problems/waif

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

int n, m, p;
bool toy_in_cat[1000];

struct Edge {
    int from, to, cap, flow;
};

struct EdmondsKarp {
    vector<Edge> edges;
    vector<int> outs[1000];

    void add(int from, int to, int cap){
        edges.push_back(Edge {from, to, cap, 0});
        outs[from].push_back(edges.size() - 1);
        edges.push_back(Edge {to, from, 0, 0});
        outs[to].push_back(edges.size() - 1);
    }

    int solve(int from, int to){
        int flow = 0;

        while (true) {
            int amount[1000];
            int route[1000];
            queue<int> q;

            memset(amount, 0, sizeof(amount));

            q.push(from);

            amount[from] = 1 << 30;
            while (!q.empty() && !amount[to]){
                int i = q.front();
                q.pop();

                for (int j = 0; j < outs[i].size(); ++j){
                    Edge &e = edges[outs[i][j]];

                    if (!amount[e.to] && e.cap > e.flow){
                        amount[e.to] = min(amount[i], e.cap - e.flow);
                        route[e.to] = outs[i][j];

                        q.push(e.to);
                    }
                }
            }
            if (!amount[to]) break;

            for (int i = to; i != from; i = edges[route[i]].from){
                edges[route[i]].flow += amount[to];
                edges[route[i] ^ 1].flow -= amount[to];
            }

            flow += amount[to];
        }

        return flow;
    }
};

EdmondsKarp ek;

int main() {
    ios_base::sync_with_stdio(false);
    cout.precision(10);

    cin >> n >> m >> p;

    for (int child = 1; child <= n; ++child){
        ek.add(0, child, 1);

        int toy_tot;
        cin >> toy_tot;

        for(int i = 1; i <= toy_tot; ++i){
            int toy;
            cin >> toy;

            ek.add(child, n + toy, 1);
        }
    }

    for (int cat = 1; cat <= p; ++cat){
        int cat_tot;
        cin >> cat_tot;

        for (int i = 1; i <= cat_tot; ++i){
            int toy;
            cin >> toy;

            ek.add(n + toy, n + m + cat, 1);
            toy_in_cat[toy] = true;
        }

        int cat_limit;
        cin >> cat_limit;

        ek.add(n + m + cat, 999, cat_limit);
    }

    for (int toy = 1; toy <= m; ++toy) {
        if (!toy_in_cat[toy]) {
            ek.add(n + toy, n + m + p + 1, 1);
        }
    }

    ek.add(n + m + p + 1, 999, 1000);

    cout << ek.solve(0, 999) << endl;

    return 0;
}
