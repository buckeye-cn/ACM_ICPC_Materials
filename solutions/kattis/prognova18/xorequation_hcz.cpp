// https://open.kattis.com/problems/xorequation

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string aa, bb, cc;
int lo, hi;

int dfs_b(int i, int a, int b) {
    if (i == bb.size()) {
        int c = a ^ b;

        if (c < lo || c >= hi) {
            return 0;
        }

        for (int i = cc.size() - 1; i >= 0; --i) {
            if (cc[i] != '?' && c % 10 != cc[i] - '0') {
                return 0;
            }

            c /= 10;
        }

        return 1;
    }

    if (bb[i] == '?') {
        int tot = 0;

        for (int d = !i && bb.size() > 1; d <= 9; ++d) {
            tot += dfs_b(i + 1, a, b * 10 + d);
        }

        return tot;
    }

    return dfs_b(i + 1, a, b * 10 + bb[i] - '0');
}

int dfs_a(int i, int a) {
    if (i == aa.size()) {
        return dfs_b(0, a, 0);
    }

    if (aa[i] == '?') {
        int tot = 0;

        for (int d = !i && aa.size() > 1; d <= 9; ++d) {
            tot += dfs_a(i + 1, a * 10 + d);
        }

        return tot;
    }

    return dfs_a(i + 1, a * 10 + aa[i] - '0');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> aa >> bb >> bb >> cc >> cc;

    int na = 0;
    for (char i: aa) {
        na += i == '?';
    }

    int nb = 0;
    for (char i: bb) {
        nb += i == '?';
    }

    int nc = 0;
    for (char i: cc) {
        nc += i == '?';
    }

    if (na + nb <= 6) {
        // ab
        // nothing
    } else if (nb + nc <= 6) {
        // bc
        swap(aa, cc);
    } else {
        // ac
        swap(bb, cc);
    }

    lo = cc.size() > 1;
    hi = 10;
    for (int i = 1; i < cc.size(); ++i) {
        lo *= 10;
        hi *= 10;
    }

    cout << dfs_a(0, 0) << endl;

    return 0;
}
