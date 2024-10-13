// https://open.kattis.com/problems/geneticreconstruction

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int p1[20];
int p2[20];
char c[20];
int vroot[20];
char vmin[20];
char vmax[20];
char vbest[20];

void dfs(int i) {
    if (i == n) {
        for (int j = 0; j < n; ++j) {
            char cc = vroot[j] >= 0 ? vmin[vroot[j]] : c[~vroot[j]];
            if (vbest[j] < cc) return;
            if (vbest[j] > cc) break;
        }

        for (int j = 0; j < n; ++j) {
            vbest[j] = vroot[j] >= 0 ? vmin[vroot[j]] : c[~vroot[j]];
        }
    } else if (p1[i] < 0) {
        vroot[i] = i;
        dfs(i + 1);
    } else {
        for (int step = 0; step < 2; ++step) {
            swap(p1[i], p2[i]);

            bool ok = true;
            char vmin1_bak = vroot[p1[i]] >= 0 ? vmin[vroot[p1[i]]] : 0;
            char vmax1_bak = vroot[p1[i]] >= 0 ? vmax[vroot[p1[i]]] : 0;

            if (c[p1[i]] != c[i]) {
                if (vroot[p1[i]] >= 0) {
                    vmin[vroot[p1[i]]] = max(vmin[vroot[p1[i]]], c[i]);
                    vmax[vroot[p1[i]]] = min(vmax[vroot[p1[i]]], c[i]);

                    ok = vmin[vroot[p1[i]]] <= vmax[vroot[p1[i]]];
                } else {
                    ok = c[~vroot[p1[i]]] == c[i];
                }
            }

            if (ok) {
                char vmin2_bak = vroot[p2[i]] >= 0 ? vmin[vroot[p2[i]]] : 0;
                char vmax2_bak = vroot[p2[i]] >= 0 ? vmax[vroot[p2[i]]] : 0;

                if (c[p2[i]] >= c[i]) {
                    vroot[i] = ~p2[i];
                    dfs(i + 1);
                }

                if (vroot[p2[i]] >= 0) {
                    vmin[vroot[p2[i]]] = max(vmin[vroot[p2[i]]], c[i]);

                    ok = vmin[vroot[p2[i]]] <= vmax[vroot[p2[i]]] && (vmin[vroot[p2[i]]] != c[p2[i]] || vmax[vroot[p2[i]]] != c[p2[i]]);
                } else {
                    ok = c[~vroot[p2[i]]] >= c[i] && c[~vroot[p2[i]]] != c[p2[i]];
                }

                if (ok) {
                    vroot[i] = vroot[p2[i]];
                    dfs(i + 1);
                }

                if (vroot[p2[i]] >= 0) vmin[vroot[p2[i]]] = vmin2_bak;
                if (vroot[p2[i]] >= 0) vmax[vroot[p2[i]]] = vmax2_bak;
            }

            if (vroot[p1[i]] >= 0) vmin[vroot[p1[i]]] = vmin1_bak;
            if (vroot[p1[i]] >= 0) vmax[vroot[p1[i]]] = vmax1_bak;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    char cmax = 'a';

    for (int i = 0; i < n; ++i) {
        cin >> p1[i] >> p2[i] >> c[i];
        p1[i] -= 1;
        p2[i] -= 1;

        cmax = max(cmax, c[i]);
    }

    for (int i = 0; i < n; ++i) {
        vmin[i] = c[i];
        vmax[i] = cmax;
        vbest[i] = 'z';
    }

    dfs(0);

    if (vbest[0] < 'z') {
        for (int i = 0; i < n; ++i) {
            cout << c[i] << vbest[i] << endl;
        }
    } else {
        cout << -1 << endl;
    }

    return 0;
}
