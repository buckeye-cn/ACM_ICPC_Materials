// https://open.kattis.com/problems/rotatetoroot

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int l[100001];
int r[100001];
int p[100001];
int v[100001];
int vl[100001];
int vr[100001];
int vx[100001];

void dfs0(int i) {
    if (l[i]) {
        dfs0(l[i]);
    }

    if (r[i]) {
        dfs0(r[i]);
    }

    v[i] = max(v[l[i]], v[r[i]]) + 1;
}

void dfs1(int i, int ll, int rr) {
    vl[i] = ll;
    vr[i] = rr;

    if (l[i]) {
        vr[i] += v[l[i]];
    }

    if (r[i]) {
        vl[i] += v[r[i]];
    }

    if (l[i]) {
        vx[l[i]] = max(vx[i], vl[i]);
        dfs1(l[i], ll + 1, rr);
    }

    if (r[i]) {
        vx[r[i]] = max(vx[i], vr[i]);
        dfs1(r[i], ll, rr + 1);
    }
}

void dfs2(int i) {
    if (l[i]) {
        dfs2(l[i]);
    }

    if (r[i]) {
        dfs2(r[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(p, 0, sizeof(p));
        memset(v, 0, sizeof(v));
        memset(vl, 0, sizeof(vl));
        memset(vr, 0, sizeof(vr));
        memset(vx, 0, sizeof(vx));

        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        for (int i = 1; i <= n; ++i) {
            cin >> l[i] >> r[i];
            p[l[i]] = i;
            p[r[i]] = i;
        }

        int root = -1;
        for (int i = 1; i <= n; ++i) {
            if (!p[i]) {
                root = i;
            }
        }

        dfs0(root);
        dfs1(root, 0, 0);
        dfs2(root);

        for (int i = 1; i <= n; ++i) {
            if (i == root) {
                cout << v[i] << endl;
            } else {
                cout << max(max(vl[i] + 1, vr[i] + 1), vx[i] + 2) << endl;
            }
        }
    }
}
