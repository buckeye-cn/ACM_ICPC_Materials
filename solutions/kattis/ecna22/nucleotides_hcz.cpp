// https://open.kattis.com/problems/nucleotides

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int aa[50001];
int tt[50001];
int gg[50001];
int cc[50001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    int n;
    cin >> s >> n;

    for (int i = 0; i < s.size(); ++i) {
        aa[i + 1] = aa[i] + (s[i] == 'A');
        tt[i + 1] = tt[i] + (s[i] == 'T');
        gg[i + 1] = gg[i] + (s[i] == 'G');
        cc[i + 1] = cc[i] + (s[i] == 'C');
    }

    for (int i = 0; i < n; ++i) {
        int s, e;
        cin >> s >> e;

        int atgc[4];

        atgc[0] = 0 - 4 * (aa[e] - aa[s - 1]);
        atgc[1] = 1 - 4 * (tt[e] - tt[s - 1]);
        atgc[2] = 2 - 4 * (gg[e] - gg[s - 1]);
        atgc[3] = 3 - 4 * (cc[e] - cc[s - 1]);

        if (atgc[0] > atgc[1]) swap(atgc[0], atgc[1]);
        if (atgc[1] > atgc[2]) swap(atgc[1], atgc[2]);
        if (atgc[2] > atgc[3]) swap(atgc[2], atgc[3]);
        if (atgc[0] > atgc[1]) swap(atgc[0], atgc[1]);
        if (atgc[1] > atgc[2]) swap(atgc[1], atgc[2]);
        if (atgc[0] > atgc[1]) swap(atgc[0], atgc[1]);

        cout << "ATGC"[atgc[0] & 3] << "ATGC"[atgc[1] & 3] << "ATGC"[atgc[2] & 3] << "ATGC"[atgc[3] & 3] << endl;
    }

    return 0;
}
