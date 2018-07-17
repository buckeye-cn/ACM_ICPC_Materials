// https://open.kattis.com/problems/initials

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

set<pair<string, int>> names;
int len[1000];
string s[1000][80];
int dp[1000][80];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;

        for (char &c: a) {
            c = tolower(c);
        }
        for (char &c: b) {
            c = tolower(c);
        }

        names.insert({b + a, b.size()});
    }

    int i = 0;
    for (const pair<string, int> &name: names) {
        len[i] = name.first.size() - 1;

        for (int j = 0; j < len[i]; ++j) {
            if (j < name.second) {
                s[i][j] = name.first.substr(0, j + 1) + name.first[name.second];
            } else {
                s[i][j] = name.first.substr(0, j + 2);
            }
        }

        ++i;
    }

    for (int j = 0; j < len[0]; ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            dp[i][j] = 1 << 30;

            for (int k = 0; k < len[i - 1]; ++k) {
                if (s[i - 1][k] < s[i][j]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + j);
                }
            }
        }
    }

    int result = 1 << 30;
    for (int j = 0; j < len[n - 1]; ++j) {
        result = min(result, dp[n - 1][j]);
    }

    cout << result << endl;

    return 0;
}
