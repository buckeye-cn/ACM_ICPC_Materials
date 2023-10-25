// https://open.kattis.com/problems/parovi

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

long dp1[50001][16];
long dp2[50001][16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s1, s2;
    cin >> s1 >> s2;

    for (int i = 0; i * 2 < s1.size(); ++i) {
        swap(s1[i], s1[s1.size() - 1 - i]);
    }

    for (int i = 0; i * 2 < s2.size(); ++i) {
        swap(s2[i], s2[s2.size() - 1 - i]);
    }

    for (int i = s1.size(); i < s2.size(); ++i) {
        s1.push_back('0');
    }

    for (int mode = 0; mode < 16; ++mode) {
        dp1[0][mode] = 1;
    }

    for (int i = 0; i < s1.size(); ++i) {
        for (int mode = 0; mode < 16; ++mode) {
            int jmin = mode & 1 ? s1[i] - '0' : 0;
            int jmax = mode & 2 ? s2[i] - '0' : 9;
            int kmin = mode & 4 ? s1[i] - '0' : 0;
            int kmax = mode & 8 ? s2[i] - '0' : 9;

            for (int j = jmin; j <= jmax; ++j) {
                for (int k = kmin; k <= kmax; ++k) {
                    int mode_new = mode & ((j == jmin) | (j == jmax) << 1 | (k == kmin) << 2 | (k == kmax) << 3);

                    dp1[i + 1][mode] += dp1[i][mode_new];
                    dp2[i + 1][mode] += dp2[i][mode_new] + abs(j - k) * dp1[i][mode_new];
                }
            }

            dp1[i + 1][mode] %= MOD;
            dp2[i + 1][mode] %= MOD;
            // cerr << i + 1 << ' ' << mode << ' ' << dp1[i + 1][mode] << endl;
            // cerr << i + 1 << ' ' << mode << ' ' << dp2[i + 1][mode] << endl;
        }
    }

    cout << dp2[s1.size()][15] << endl;

    return 0;
}
