#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int m;
int to[400000];
long cnt[400000];
long wcnt[400000];
long n[2];
vector<int> conn[2][100000];
long ww[2][100000];

void dfs(int i, int p) {
    if (!cnt[p]) {
        int j = to[p];

        if (ww[i][j]) {
            cnt[p] = n[i] - cnt[p ^ 1];
            wcnt[p] = ww[i][j] - wcnt[p ^ 1] + cnt[p];
        } else {
            for (int k = 0; k < conn[i][j].size(); ++k) {
                int pp = conn[i][j][k];

                if (pp != (p ^ 1)) {
                    dfs(i, pp);
                    cnt[p] += cnt[pp];
                    wcnt[p] += wcnt[pp];
                }
            }

            cnt[p] += 1;
            wcnt[p] += cnt[p];

            if (cnt[p ^ 1]) {
                for (int k = 0; k < conn[i][j].size(); ++k) {
                    int pp = conn[i][j][k];

                    ww[i][j] += wcnt[pp];
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        m = 0;

        int c;
        cin >> n[0] >> n[1] >> c;

        long base = (n[0] + n[1]) * (n[0] + n[1] - 1) / 2;
        long intra = 0;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n[i]; ++j) {
                conn[i][j].clear();
                ww[i][j] = 0;
            }

            for (int j = 0; j < n[i] - 1; ++j) {
                int x;
                cin >> x;

                to[m] = x - 1;
                cnt[m] = 0;
                wcnt[m] = 0;
                conn[i][j].push_back(m);
                m += 1;

                to[m] = j;
                cnt[m] = 0;
                wcnt[m] = 0;
                conn[i][x - 1].push_back(m);
                m += 1;
            }

            for (int j = 0; j < n[i]; ++j) {
                for (int k = 0; k < conn[i][j].size(); ++k) {
                    dfs(i, conn[i][j][k]);
                }
            }

            for (int j = 0; j < n[i]; ++j) {
                if (ww[i][j]) continue;

                for (int k = 0; k < conn[i][j].size(); ++k) {
                    int pp = conn[i][j][k];

                    ww[i][j] += wcnt[pp];
                }
            }
        }

        for (int i = 0; i < m; i += 2) {
            intra += cnt[i] * cnt[i ^ 1];
        }

        for (int i = 0; i < c; ++i) {
            int a, b;
            cin >> a >> b;

            long inter = ww[0][a - 1] * n[1] + ww[1][b - 1] * n[0];


            if (i) {
                cout << ' ';
            }

            cout << double(intra + inter + n[0] * n[1]) / base;
        }

        cout << endl;
    }

    return 0;
}
