// https://open.kattis.com/problems/ebonyandivory

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int cost[2][2][6][6][13];
int note[10000];
int dp[10000][6];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    char keys[] = "_wbwwbwbwwbwbwbwwbwbwwbwbwbwwbwbwwbwbwbwwbwbwwbwbwbwwbwbwwbwbwbwwbwbwwbwbwbwwbwbwwbwbwbww";

    int n[2][2];
    int l;
    cin >> n[0][0] >> n[0][1] >> n[1][0] >> n[1][1] >> l;

    for (int c1 = 0; c1 < 2; ++c1) {
        for (int c2 = 0; c2 < 2; ++c2) {
            for (int lo = 1; lo <= 5; ++lo) {
                for (int hi = 1; hi <= 5; ++hi) {
                    for (int d = 1; d <= 12; ++d) {
                        cost[c1][c2][lo][hi][d] = 1e9;
                    }
                }
            }

            for (int i = 0; i < n[c1][c2]; ++i) {
                int lo, hi;
                cin >> lo >> hi;

                for (int d = 1; d <= 12; ++d) {
                    cin >> cost[c1][c2][lo][hi][d];
                }
            }
        }
    }

    cin >> note[0];

    for (int i = 1; i < l; ++i) {
        cin >> note[i];

        int c1 = keys[note[i - 1]] == 'b';
        int c2 = keys[note[i]] == 'b';

        // cerr << note[i - 1] << keys[note[i - 1]] << ' ' << note[i] << keys[note[i]] << endl;

        for (int f2 = 1; f2 <= 5; ++f2) {
            dp[i][f2] = 1e9;

            if (note[i - 1] < note[i]) {
                for (int f1 = 1; f1 <= 5; ++f1) {
                    if (f1 != f2) {
                        dp[i][f2] = min(dp[i][f2], dp[i - 1][f1] + cost[c1][c2][f1][f2][note[i] - note[i - 1]]);
                    }
                }
            } else if (note[i - 1] > note[i]) {
                for (int f1 = 1; f1 <= 5; ++f1) {
                    if (f1 != f2) {
                        dp[i][f2] = min(dp[i][f2], dp[i - 1][f1] + cost[c2][c1][f2][f1][note[i - 1] - note[i]]);
                    }
                }
            } else {
                for (int f = 1; f <= 5; ++f) {
                    dp[i][f] = dp[i - 1][f];
                }
            }

            // cerr << f2 << ' ' << dp[i][f2] << endl;
        }
    }

    int result = 1e9;

    for (int f = 1; f <= 5; ++f) {
        result = min(result, dp[l - 1][f]);
    }

    cout << result << endl;

    return 0;
}
