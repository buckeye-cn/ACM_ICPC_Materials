// https://open.kattis.com/problems/tipofyourtongue

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int trie_size[4000004];
int trie_next[4000004][26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, q;
    cin >> n >> q;

    int m = 4;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        int pf = 1;
        int pb = 2;
        int pfb = 3;

        auto add = [&](int &p, char c) {
            if (!trie_next[p][c - 'a']) {
                trie_next[p][c - 'a'] = m++;
            }

            p = trie_next[p][c - 'a'];
            trie_size[p] += 1;
        };

        for (int j = 0; j < s.size(); ++j) {
            add(pf, s[j]);
            add(pb, s[s.size() - 1 - j]);
            add(pfb, s[j]);
            add(pfb, s[s.size() - 1 - j]);
        }
    }

    for (int i = 0; i < q; ++i) {
        string o, sf, sb;
        cin >> o >> sf >> sb;

        int pf = 1;
        int pb = 2;
        int pfb = 3;

        for (int j = 0; j < sf.size(); ++j) {
            pf = trie_next[pf][sf[j] - 'a'];
            pb = trie_next[pb][sb[sb.size() - 1 - j] - 'a'];
            pfb = trie_next[pfb][sf[j] - 'a'];
            pfb = trie_next[pfb][sb[sb.size() - 1 - j] - 'a'];
        }

        if (o[0] == 'A') {
            cout << trie_size[pfb] << endl;
        } else if (o[0] == 'O') {
            cout << trie_size[pf] + trie_size[pb] - trie_size[pfb] << endl;
        } else {
            cout << trie_size[pf] + trie_size[pb] - 2 * trie_size[pfb] << endl;
        }
    }

    return 0;
}
