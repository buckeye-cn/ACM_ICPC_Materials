// https://open.kattis.com/problems/phonelist

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int trie[100000][10];
char trie_def[100000];
int trie_tot;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        memset(trie, 0, sizeof(trie));
        memset(trie_def, 0, sizeof(trie_def));
        int trie_tot = 1;

        int m;
        cin >> m;

        bool fail = false;

        for (int j = 0; j < m; ++j) {
            string s;
            cin >> s;

            if (fail) {
                continue;
            }

            int p = 0;
            for (char c: s) {
                if (!trie[p][c - '0']) {
                    trie[p][c - '0'] = trie_tot++;

                    if (trie_def[p] == 'L') {
                        fail = true;
                        break;
                    } else {
                        trie_def[p] = 'P';
                    }
                }

                p = trie[p][c - '0'];
            }

            if (trie_def[p]) {
                fail = true;
            } else {
                trie_def[p] = 'L';
            }
        }

        cout << (fail ? "NO" : "YES") << endl;
    }

    return 0;
}
