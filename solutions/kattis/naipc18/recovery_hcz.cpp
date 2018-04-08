// https://open.kattis.com/problems/recovery

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool zero[60][60];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string a, b;
    cin >> a >> b;

    int na = 0;
    int nb = 0;
    char ca = b.size() & 1 ? '0' : '1';
    char cb = a.size() & 1 ? '0' : '1';
    for (char c: a) {
        if (c == ca) {
            ++na;
        }
    }
    for (char c: b) {
        if (c == cb) {
            ++nb;
        }
    }

    if ((na - nb) & 1) {
        cout << -1 << endl;

        return 0;
    }

    int i = 0;
    int j = 0;
    for (; na > nb; --na, ++i) {
        while (i < a.size() && a[i] != ca) ++i;
        zero[i][0] = true;
    }
    for (; na < nb; --nb, ++j) {
        while (j < b.size() && b[j] != cb) ++j;
        zero[0][j] = true;
    }
    for (; na; --na, ++i, ++j) {
        while (i < a.size() && a[i] != ca) ++i;
        while (j < b.size() && b[j] != cb) ++j;
        zero[i][j] = true;
    }

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            cout << !zero[i][j];
        }

        cout << endl;
    }

    return 0;
}
