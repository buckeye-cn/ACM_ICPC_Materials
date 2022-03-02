// https://open.kattis.com/problems/abridgedreading

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int page[1001];
bool is_dep[1001];
int n_dep[1001];
int dep[1001][1000];
int visited[1001];

int dfs(int from, int p, int q) {
    int r = page[from];

    for (int i = 0; i < n_dep[from]; ++i) {
        int to = dep[from][i];

        if (visited[to] == p || visited[to] == q) {
            continue;
        }

        visited[to] = q;

        r += dfs(to, p, q);
    }

    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> page[i];
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;

        is_dep[a] = true;
        dep[b][n_dep[b]++] = a;
    }

    int best = 1e9;

    for (int i = 1; i < n; ++i) {
        if (is_dep[i]) continue;

        int v1 = dfs(i, i * 1001, i * 1001);

        for (int j = i + 1; j <= n; ++j) {
            if (is_dep[j]) continue;

            int v2 = dfs(j, i * 1001, i * 1001 + j);

            best = min(best, v1 + v2);
        }
    }

    cout << best << endl;

    return 0;
}
