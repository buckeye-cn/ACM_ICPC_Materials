// https://open.kattis.com/problems/flashingfluorescents

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool dp[32][65536];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    int mask = (1 << s.size()) - 1;
    int init = 0;

    for (char c: s) {
        init <<= 1;

        if (c == '1') {
            init ^= 1;
        }
    }

    dp[0][init] = true;

    for (int i = 1; true; ++i) {
        if (dp[i - 1][mask]) {
            cout << i - 1 << endl;

            break;
        }

        for (int j = 0; j < 1 << s.size(); ++j) {
            if (dp[i - 1][j]) {
                dp[i][j] = true;

                int flip = ((1 << i) - 1) << (s.size() - i);

                for (int k = 0; flip; ++k) {
                    dp[i][j ^ flip] = true;
                    flip >>= 1;
                }
            }
        }
    }

    return 0;
}
