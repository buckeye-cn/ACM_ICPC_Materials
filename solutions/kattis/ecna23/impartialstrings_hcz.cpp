// https://open.kattis.com/problems/impartialstrings

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string a;
string s[2];
int kmp[2][1501];
bool dp[1500][1500][5];

void dfs(int i, int j, int n) {
    if (n < 0 || n > 4 || dp[i][j][n]) {
        return;
    }

    dp[i][j][n] = true;

    for (char c: a) {
        int ii = i;
        int jj = j;
        int nn = n;

        while (s[0][ii] != c && ii >= 0) {
            ii = kmp[0][ii];
        }

        while (s[1][jj] != c && jj >= 0) {
            jj = kmp[1][jj];
        }

        ii += 1;
        jj += 1;

        if (ii == s[0].size()) {
            ii = kmp[0][ii];
            nn += 1;
        }

        if (jj == s[1].size()) {
            jj = kmp[1][jj];
            nn -= 1;
        }

        dfs(ii, jj, nn);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int kk;
    cin >> kk;

    while (kk--) {
        memset(dp, 0, sizeof(dp));

        cin >> a >> s[0] >> s[1];

        for (int i = 0; i < 2; ++i) {
            kmp[i][0] = -1;

            for (int j = 1, k = 0; j <= s[i].size(); ++j, ++k) {
                if (j == s[i].size()) {
                    kmp[i][j] = k;
                } else if (s[i][j] == s[i][k]) {
                    kmp[i][j] = kmp[i][k];
                } else {
                    kmp[i][j] = k;

                    while (k >= 0 && s[i][j] != s[i][k]) {
                        k = kmp[i][k];
                    }
                }
            }
        }

        dfs(0, 0, 2);

        int ok1 = 1;
        int ok2 = 1;

        for (int i = 0; i < s[0].size(); ++i) {
            for (int j = 0; j < s[1].size(); ++j) {
                if (dp[i][j][2]) {
                    if (dp[i][j][0]) {
                        ok1 = 0;
                    }
                    if (dp[i][j][4]) {
                        ok2 = 0;
                    }
                }
            }
        }

        cout << (ok1 | ok2) << endl;
    }

    return 0;
}
