// https://open.kattis.com/problems/oop
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int pre_tot = 1;
int pre[5000000][26];
int pre_post[5000000];
int post_tot = 1;
int post[5000000][26];
int post_fin[5000000];
int count_cache[5000000];

int count(int p) {
    if (!count_cache[p]) {
        count_cache[p] = post_fin[p];

        for (int i = 0; i < 26; ++i) {
            if (post[p][i]) {
                count_cache[p] += count(post[p][i]);
            }
        }
    }

    return count_cache[p];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        for (int j = 0; j <= s.size(); ++j) {
            int p = 0;

            for (int k = 0; k < j; ++k) {
                if (!pre[p][s[k] - 'a']) {
                    pre[p][s[k] - 'a'] = pre_tot++;
                }

                p = pre[p][s[k] - 'a'];
            }

            if (!pre_post[p]) {
                pre_post[p] = post_tot++;
            }

            p = pre_post[p];

            for (int k = s.size() - 1; k >= j; --k) {
                if (!post[p][s[k] - 'a']) {
                    post[p][s[k] - 'a'] = post_tot++;
                }

                p = post[p][s[k] - 'a'];
            }

            post_fin[p] += 1;
        }
    }

    // for (int i = 0; i < pre_tot; ++i) {
    //     cout << "pre " << i;
    //     for (int j = 0; j < 26; ++j) {
    //         if (pre[i][j]) {
    //             cout << ' ' << char(j + 'a') << pre[i][j];
    //         }
    //     }
    //     cout << ' ' << pre_post[i] << endl;
    // }

    // for (int i = 0; i < post_tot; ++i) {
    //     cout << "post " << i;
    //     for (int j = 0; j < 26; ++j) {
    //         if (post[i][j]) {
    //             cout << ' ' << char(j + 'a') << post[i][j];
    //         }
    //     }
    //     cout << ' ' << post_fin[i] << endl;
    // }

    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;

        int p = 0;

        for (int k = 0; s[k] != '*'; ++k) {
            if (!pre[p][s[k] - 'a']) {
                goto fail;
            }

            p = pre[p][s[k] - 'a'];
        }

        p = pre_post[p];

        for (int k = s.size() - 1; s[k] != '*'; --k) {
            if (!post[p][s[k] - 'a']) {
                goto fail;
            }

            p = post[p][s[k] - 'a'];
        }

        cout << count(p) << endl;
        continue;

        fail:;

        cout << 0 << endl;
    }

    return 0;
}
