// https://open.kattis.com/problems/burrowswheeler

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

pair<long, int> dp[18][100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;

    while (getline(cin, s)) {
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < s.size(); ++i) {
            dp[0][i] = {s[i], i};
        }

        for (int i = 0; i < 17; ++i) {
            sort(dp[i], dp[i] + s.size());

            long pos = 0;

            for (int j = 0; j < s.size(); ++j) {
                pos += j && dp[i][j - 1].first < dp[i][j].first;
                dp[i + 1][dp[i][j].second].first += pos << 32;
                dp[i + 1][dp[i][j].second].second = dp[i][j].second;

                if (dp[i][j].second >= 1 << i) {
                    dp[i + 1][dp[i][j].second - (1 << i)].first += pos;
                } else {
                    dp[i + 1][dp[i][j].second + s.size() - (1 << i)].first += pos;
                }
            }
        }

        sort(dp[17], dp[17] + s.size());

        for (int i = 0; i < s.size(); ++i) {
            if (dp[17][i].second) {
                cout << s[dp[17][i].second - 1];
            } else {
                cout << s[s.size() - 1];
            }
        }

        cout << endl;
    }

    return 0;
}
