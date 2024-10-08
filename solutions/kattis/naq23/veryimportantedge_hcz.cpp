// https://open.kattis.com/problems/veryimportantedge

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int a[1000000];
int b[1000000];
pair<int, int> w[1000000];

int group[100000];
bool used[1000000];
vector<pair<int, int>> to[100000];

int parent[100000];
int level[100000];
int weight[100000];

int find(int g) {
    int root = g;

    while (root != group[root]) {
        root = group[root];
    }

    int curr = g;

    while (curr != root) {
        int prev = curr;

        curr = group[prev];
        group[prev] = root;
    }

    return root;
}

void dfs(int i) {
    for (pair<int, int> j: to[i]) {
        if (j.first != parent[i]) {
            parent[j.first] = i;
            level[j.first] = level[i] + 1;
            weight[j.first] = j.second;
            dfs(j.first);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> w[i].first;
        a[i] -= 1;
        b[i] -= 1;
        w[i].second = i;
    }

    sort(w, w + m);

    for (int i = 0; i < n; ++i) {
        group[i] = i;
    }

    long mst = 0;

    for (int i = 0; i < m; ++i) {
        int g1 = find(a[w[i].second]);
        int g2 = find(b[w[i].second]);

        if (g1 != g2) {
            used[w[i].second] = true;
            group[max(g1, g2)] = min(g1, g2);
            to[a[w[i].second]].push_back({b[w[i].second], w[i].first});
            to[b[w[i].second]].push_back({a[w[i].second], w[i].first});
            mst += w[i].first;
        }
    }

    dfs(0);

    int gap = 0;

    for (int i = 0; i < m; ++i) {
        if (!used[w[i].second]) {
            int pa = a[w[i].second];
            int pb = b[w[i].second];

            while (pa != pb) {
                if (level[pa] > level[pb]) {
                    pa = parent[pa];
                } else {
                    pb = parent[pb];
                }
            }

            int curr = a[w[i].second];

            while (curr != pa) {
                int prev = curr;

                gap = max(gap, w[i].first - weight[prev]);
                curr = parent[prev];
                parent[prev] = pa;
                weight[prev] = 1000000;
            }

            curr = b[w[i].second];

            while (curr != pb) {
                int prev = curr;

                gap = max(gap, w[i].first - weight[prev]);
                curr = parent[prev];
                parent[prev] = pb;
                weight[prev] = 1000000;
            }
        }
    }

    cout << mst + gap << endl;

    return 0;
}
