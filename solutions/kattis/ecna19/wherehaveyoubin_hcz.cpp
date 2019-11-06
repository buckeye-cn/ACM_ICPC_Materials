// https://open.kattis.com/problems/wherehaveyoubin

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int need[6];
int owner[150];
int item[150];

// used, curr, pos
int dp[32][6][151];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    n = s.size();

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') owner[i] = 0;
        if (s[i] == 'E') owner[i] = 1;
        if (s[i] == 'I') owner[i] = 2;
        if (s[i] == 'O') owner[i] = 3;
        if (s[i] == 'U') owner[i] = 4;
        if (s[i] == 'X') owner[i] = 5;

        cin >> item[i];

        need[owner[i]] += 1;
    }

    int d;
    cin >> d;

    for (int i = 0; i < d; ++i) {
        int bin;
        cin >> bin;

        need[owner[bin - 1]] -= 1;

        item[bin - 1] = 0;
    }

    string s_add;
    cin >> s_add;

    for (char c: s_add) {
        if (c == 'A') need[0] += 1;
        if (c == 'E') need[1] += 1;
        if (c == 'I') need[2] += 1;
        if (c == 'O') need[3] += 1;
        if (c == 'U') need[4] += 1;
    }

    for (int i = 0; i <= n; ++i) {
        if (i) {
            // consume one bin

            for (int used = 0; used < 32; ++used) {
                for (int curr = 0; curr < 5; ++curr) {
                    if (used & (1 << curr)) continue;

                    if (curr == owner[i - 1]) {
                        for (int pos = need[curr]; pos >= 1; --pos) {
                            dp[used][curr][pos] = dp[used][curr][pos - 1];
                        }
                    } else {
                        for (int pos = need[curr]; pos >= 1; --pos) {
                            dp[used][curr][pos] = dp[used][curr][pos - 1] + item[i - 1];
                        }
                    }

                    dp[used][curr][0] = 1e9;
                }

                dp[used][5][0] += item[i - 1];
            }
        } else {
            // initialize

            for (int used = 0; used < 32; ++used) {
                for (int curr = 0; curr < 5; ++curr) {
                    if (used & (1 << curr)) continue;

                    for (int pos = 0; pos <= need[curr]; ++pos) {
                        dp[used][curr][pos] = 1e9;
                    }
                }

                dp[used][5][0] = 1e9;
            }

            dp[0][5][0] = 0;
        }

        // switch curr

        for (int used = 0; used < 32; ++used) {
            for (int curr = 0; curr < 5; ++curr) {
                if (used & (1 << curr)) {
                    dp[used][5][0] = min(dp[used][5][0], dp[used ^ (1 << curr)][curr][need[curr]]);
                }
            }

            for (int curr = 0; curr < 5; ++curr) {
                if (!(used & (1 << curr))) {
                    dp[used][curr][0] = dp[used][5][0];
                }
            }
        }
    }

    cout << dp[31][5][0] << endl;

    return 0;
}
