// https://open.kattis.com/problems/pearls

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int k, n, m;
string s;
string d;
string result;
int r, c;

bool sp[62][62];

void dfs(int i, int rr, int cc) {
    if (result[0] != 'i') return;
    if (k - i < abs(rr - r) + abs(cc - c)) return;
    if (i == k) {
        if (rr != r || cc != c) return;
        if (s[k - 1] == 'B' && s[0] == 'B') return;
        if (s[k - 2] != 'B' && s[k - 1] == 'W' && s[0] != 'B') return;
        if (s[k - 1] != 'B' && s[0] == 'W' && s[1] != 'B') return;
        if ((s[0] == 'B') == (d[k - 1] == d[0])) return;

        result = d;

        return;
    }

    if (!sp[rr][cc]) return;
    sp[rr][cc] = false;

    if (s[i - 1] != 'B' && s[i] != 'W') {
        char ss = s[i];
        s[i] = 'B';

        if (d[i - 1] == 'N' || d[i - 1] == 'S') {
            d[i] = 'E';
            dfs(i + 1, rr, cc + 1);
        }

        if (d[i - 1] == 'E' || d[i - 1] == 'W') {
            d[i] = 'N';
            dfs(i + 1, rr - 1, cc);
            d[i] = 'S';
            dfs(i + 1, rr + 1, cc);
        }

        if (d[i - 1] == 'N' || d[i - 1] == 'S') {
            d[i] = 'W';
            dfs(i + 1, rr, cc - 1);
        }

        s[i] = ss;
    }

    if ((i < 2 || s[i - 2] == 'B' || s[i - 1] != 'W') && s[i] != 'B') {
        d[i] = d[i - 1];

        if (d[i - 1] == 'E') dfs(i + 1, rr, cc + 1);
        if (d[i - 1] == 'N') dfs(i + 1, rr - 1, cc);
        if (d[i - 1] == 'S') dfs(i + 1, rr + 1, cc);
        if (d[i - 1] == 'W') dfs(i + 1, rr, cc - 1);
    }

    sp[rr][cc] = true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> k >> n >> m >> s >> r >> c;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            sp[i][j] = true;
        }
    }

    sp[r][c] = false;
    d = s;
    result = "impossible";

    d[0] = 'E';
    dfs(1, r, c + 1);
    d[0] = 'N';
    dfs(1, r - 1, c);
    d[0] = 'S';
    dfs(1, r + 1, c);
    d[0] = 'W';
    dfs(1, r, c - 1);

    cout << result << endl;

    return 0;
}
