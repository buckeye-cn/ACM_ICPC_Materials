// https://open.kattis.com/problems/ispiti

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int rmap_tot = 1;
int rmap[200000 * 30][2][2];
int fmap_tot = 1;
int fmap[200001][2];

int find_a;
int find_b;
int find_i;
int best_a;
int best_b;
int best_i;

void dfs(int aa, int bb, int level, int cur) {
    // cerr << aa << ':' << bb << ' ' << level << ' ' << cur
    //     << '\t' << rmap[cur][0][0] << ' ' << rmap[cur][0][1]
    //     << ' ' << rmap[cur][1][0] << ' ' << rmap[cur][1][1] << endl;

    if (bb > best_b || (bb == best_b && aa > best_a)) {
        return;
    }

    if (level == -1) {
        if (aa >= find_a && bb >= find_b && cur != find_i) {
            best_a = aa;
            best_b = bb;
            best_i = cur;
        }

        return;
    }

    if (aa + (2l << level) <= find_a || bb + (2l << level) <= find_b) {
        return;
    }

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 2; ++i) {
            if (!rmap[cur][i][j]) continue;

            dfs(aa + (i << level), bb + (j << level), level - 1, rmap[cur][i][j]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;

        if (c == 'D') {
            int a, b;
            cin >> a >> b;

            int cur = 0;
            for (int level = 30; level > 0; --level) {
                if (!rmap[cur][(a >> level) & 1][(b >> level) & 1]) {
                    rmap[cur][(a >> level) & 1][(b >> level) & 1] = rmap_tot++;
                }

                cur = rmap[cur][(a >> level) & 1][(b >> level) & 1];
            }

            fmap[fmap_tot][0] = a;
            fmap[fmap_tot][1] = b;

            rmap[cur][a & 1][b & 1] = fmap_tot++;
        } else {
            int q;
            cin >> q;

            find_a = fmap[q][0];
            find_b = fmap[q][1];
            find_i = q;
            best_a = 0x7fffffffl;
            best_b = 0x7fffffffl;
            best_i = 0;

            dfs(0, 0, 30, 0);

            if (best_i) {
                cout << best_i << endl;
            } else {
                cout << "NE" << endl;
            }
        }
    }

    return 0;
}
