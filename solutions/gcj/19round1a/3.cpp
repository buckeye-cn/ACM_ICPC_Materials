#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int trie_tot;
int trie_next[65536][26];
int trie_count[65536];

void dfs(int pos) {
    for (int i = 0; i < 26; ++i) {
        if (trie_next[pos][i]) {
            dfs(trie_next[pos][i]);

            trie_count[pos] += trie_count[trie_next[pos][i]];
        }
    }

    if (pos && trie_count[pos] >= 2) {
        trie_count[pos] -= 2;
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

        trie_tot = 1;
        memset(trie_next, 0, sizeof(trie_next));
        memset(trie_count, 0, sizeof(trie_count));

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;

            int now = 0;
            for (int j = s.size() - 1; j >= 0; --j) {
                if (!trie_next[now][s[j] - 'A']) {
                    trie_next[now][s[j] - 'A'] = trie_tot++;
                }

                now = trie_next[now][s[j] - 'A'];
            }

            trie_count[now] = 1;
        }

        dfs(0);

        cout << n - trie_count[0] << endl;
    }

    return 0;
}
