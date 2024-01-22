// https://open.kattis.com/problems/illiteracy

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[16777216];
int q[16777216];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s, t;
    cin >> s >> t;

    int ss = 0;
    int tt = 0;

    for (int i = 0; i < 8; ++i) {
        ss |= (s[i] - 'A') << (i * 3);
        tt |= (t[i] - 'A') << (i * 3);
    }

    int head = 0;
    int tail = 0;

    dp[ss] = 1;
    q[tail++] = ss;

    while (!dp[tt]) {
        int pp = q[head++];

        for (int i = 0; i < 8; ++i) {
            int qq = pp;

            auto rot = [&](int j) {
                int v = (qq >> (j * 3)) & 7;

                qq ^= v << (j * 3);
                qq ^= ((v + 1) % 6) << (j * 3);
            };

            if (((pp >> (i * 3)) & 7) == 0) {
                if (i) rot(i - 1);
                if (i <= 6) rot(i + 1);
            } else if (((pp >> (i * 3)) & 7) == 1) {
                if (i && i <= 6) {
                    int vl = (qq >> (i * 3 - 3)) & 7;
                    int vr = (qq >> (i * 3 + 3)) & 7;

                    qq ^= vr << (i * 3 + 3);
                    qq ^= vl << (i * 3 + 3);
                }
            } else if (((pp >> (i * 3)) & 7) == 2) {
                rot(7 - i);
            } else if (((pp >> (i * 3)) & 7) == 3) {
                for (int j = 0; j < 8; ++j) {
                    if (i <= 3 ? j < i : j > i) {
                        rot(j);
                    }
                }
            } else if (((pp >> (i * 3)) & 7) == 4) {
                if (i && i <= 6) {
                    rot(i - min(i, 7 - i));
                    rot(i + min(i, 7 - i));
                }
            } else if (((pp >> (i * 3)) & 7) == 5) {
                rot("51627384"[i] - '1');
            }

            if (!dp[qq]) {
                dp[qq] = dp[pp] + 1;
                q[tail++] = qq;
            }
        }
    }

    cout << dp[tt] - dp[ss] << endl;

    return 0;
}
