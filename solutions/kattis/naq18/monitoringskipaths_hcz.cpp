// https://open.kattis.com/problems/monitoringskipaths

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int tree_child[260000];
int tree_next[260000];

int path_child[260000];
int path_next[260000];
int path_end[260000];

bool sorted[260000];
bool marked[260000];

int order_n;
int order[260000];

void dfs_sort(int i) {
    if (!sorted[i]) {
        for (int j = tree_child[i]; j; j = tree_next[j]) {
            dfs_sort(j);
        }

        sorted[i] = true;
        order[order_n++] = i;
    }
}

void dfs_mark(int i) {
    if (!marked[i]) {
        for (int j = tree_child[i]; j; j = tree_next[j]) {
            dfs_mark(j);
        }

        marked[i] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, k, m;
    cin >> n >> k >> m;

    for (int i = 1; i <= k; ++i) {
        int u, v;
        cin >> u >> v;

        tree_next[v] = tree_child[u];
        tree_child[u] = v;
    }

    for (int i = 1; i <= m; ++i) {
        int s;
        cin >> s >> path_end[i];

        path_next[i] = path_child[s];
        path_child[s] = i;
    }

    for (int i = 1; i <= n; ++i) {
        dfs_sort(i);
    }

    int result = 0;

    for (int i = 1; i <= n; ++i) {
        bool active = false;

        for (int j = path_child[order[i]]; j && !active; j = path_next[j]) {
            active = !marked[path_end[j]];
        }

        if (active) {
            result += 1;

            dfs_mark(order[i]);
        }
    }

    cout << result << endl;

    return 0;
}
