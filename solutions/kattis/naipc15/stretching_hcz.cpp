// https://open.kattis.com/problems/stretching

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

bool dp[201][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    unordered_set<string> visited;

    for (int len = 1; len <= s.size(); ++len) {
        if (s.size() % len) continue;

        for (int pos = 0; pos + len <= s.size(); ++pos) {
            if (s[pos] != s[0] || s[pos + len - 1] != s[s.size() - 1]) continue;

            string ss {&s[pos], &s[pos + len]};

            if (visited.find(ss) != visited.end()) continue;
            visited.insert(ss);

            for (int p = 0; p + len <= s.size(); ++p) {
                dp[0][p] = true;
            }

            for (int i = 0; i < s.size(); i += len) {
                for (int l = 1; l <= len; ++l) {
                    for (int p = 0; p + i + len <= s.size(); ++p) {
                        dp[i + l][p] = dp[i + l - 1][p] && s[p + i + l - 1] == ss[l - 1];

                        for (int j = len; j <= i; j += len) {
                            dp[i + l][p] |= dp[i - j + l][p] && dp[j][p + i - j + l];
                        }
                    }
                }
            }

            if (dp[s.size()][0]) {
                cout << ss << endl;

                return 0;
            }
        }
    }
}
