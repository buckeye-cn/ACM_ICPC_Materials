// https://open.kattis.com/problems/lost

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

int n, m;
map<string, int> langs = {{"English", 0}};
long cost[128][128];
int dist[128];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        langs[s] = i + 1;
    }

    for (int i = 0; i < m; ++i) {
        string s1, s2;
        cin >> s1 >> s2;

        long c;
        cin >> c;
        cost[langs[s1]][langs[s2]] = c;
        cost[langs[s2]][langs[s1]] = c;
    }

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int i = q.front();
        q.pop();

        for (int j = 1; j <= n; ++j) {
            if (cost[i][j] && !dist[j]) {
                dist[j] = dist[i] + 1;
                q.push(j);
            }
        }
    }

    long tot_cost = 0;
    for (int i = 1; i <= n; ++i) {
        long min_cost = 1l << 62;

        for (int j = 0; j <= n; ++j) {
            if (cost[j][i] && dist[j] + 1 == dist[i]) {
                if (min_cost > cost[j][i]) {
                    min_cost = cost[j][i];
                }
            }
        }

        if (min_cost != 1l << 62) {
            tot_cost += min_cost;
        } else {
            cout << "Impossible" << endl;

            return 0;
        }
    }

    cout << tot_cost << endl;

    return 0;
}
