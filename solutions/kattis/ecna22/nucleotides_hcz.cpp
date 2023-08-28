// https://open.kattis.com/problems/nucleotides

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
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

        set<pair<int, char>> atgc;

        atgc.insert({-4 * (aa[e] - aa[s - 1]) - 3, 'A'});
        atgc.insert({-4 * (tt[e] - tt[s - 1]) - 2, 'T'});
        atgc.insert({-4 * (gg[e] - gg[s - 1]) - 1, 'G'});
        atgc.insert({-4 * (cc[e] - cc[s - 1])    , 'C'});

        for (pair<int, char> p: atgc) {
            cout << p.second;
        }
        cout << endl;
    }

    return 0;
}
