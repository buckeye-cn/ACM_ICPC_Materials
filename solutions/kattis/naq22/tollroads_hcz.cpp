// https://open.kattis.com/problems/tollroads

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m, q;
int u[200000];
int v[200000];
pair<int, int> t[200000];

int group[400000];
int tree_l[200000];
int tree_r[200000];
int tree_tmax[200000];
int tree_count[200000];

int seg_n = 524288;
int i_seg[200001];
int seg_i[1048576];
int seg_tmax[1048576];
int seg_count[1048576];

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

void dfs(int i, int tmax, int count) {
    if (i > n) {
        if (tree_tmax[i - n] == tmax) {
            tree_count[i - n] = count;
        }

        dfs(tree_l[i - n], tree_tmax[i - n], tree_count[i - n]);
        seg_i[seg_n] = i;
        seg_tmax[seg_n] = tree_tmax[i - n];
        seg_count[seg_n] = tree_count[i - n];
        seg_n += 1;
        dfs(tree_r[i - n], tree_tmax[i - n], tree_count[i - n]);
    } else {
        i_seg[i] = seg_n;
        seg_i[seg_n] = i;
        seg_tmax[seg_n] = 0;
        seg_count[seg_n] = 1;
        seg_n += 1;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m >> q;

    for (int i = 1; i < 2 * n; ++i) {
        group[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i] >> t[i].first;
        t[i].second = i;
    }

    sort(t, t + m);

    int k = 1;

    for (int i = 0; i < m; ++i) {
        int g1 = find(u[t[i].second]);
        int g2 = find(v[t[i].second]);

        if (g1 != g2) {
            group[g1] = n + k;
            group[g2] = n + k;
            tree_l[k] = g1;
            tree_r[k] = g2;
            tree_tmax[k] = t[i].first;
            tree_count[k] = (g1 <= n ? 1 : tree_count[g1 - n]) + (g2 <= n ? 1 : tree_count[g2 - n]);
            k += 1;
        }
    }

    dfs(2 * n - 1, -1, -1);

    for (int i = 262144; i > 0; i >>= 1) {
        for (int j = i; j < 2 * i; ++j) {
            seg_tmax[j] = max(seg_tmax[2 * j], seg_tmax[2 * j + 1]);
            seg_count[j] = max(seg_count[2 * j], seg_count[2 * j + 1]);
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;

        int l = min(i_seg[a], i_seg[b]);
        int r = max(i_seg[a], i_seg[b]);
        int tmax = 0;
        int count = 0;

        while (l <= r) {
            tmax = max(tmax, seg_tmax[l]);
            tmax = max(tmax, seg_tmax[r]);
            count = max(count, seg_count[l]);
            count = max(count, seg_count[r]);
            l = (l + 1) >> 1;
            r = (r - 1) >> 1;
        }

        cout << tmax << ' ' << count << endl;
    }

    return 0;
}
