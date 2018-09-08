// https://open.kattis.com/problems/uxuhulvoting

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int m;
int pref[100][8];

bool dp[101][8][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> m;

        for (int j = 0; j < m; ++j) {
            for (int f = 0; f < 8; ++f) {
                cin >> pref[j][f];
            }
        }

        memset(dp, 0, sizeof(dp));

        for (int f = 0; f < 8; ++f) {
            dp[m][f][f] = true;
        }

        for (int j = m - 1; j >= 0; --j) {
            for (int b = 0; b < 8; ++b) {
                int best = 9;
                int best_f;

                for (int e = 0; e < 8; ++e) {
                    if ((b ^ e) != 1 && (b ^ e) != 2 && (b ^ e) != 4) continue;

                    int worst = 0;
                    int worst_f;

                    for (int f = 0; f < 8; ++f) {
                        if (!dp[j + 1][e][f]) continue;

                        if (worst < pref[j][f]) {
                            worst = pref[j][f];
                            worst_f = f;
                        }
                    }

                    if (best > worst) {
                        best = worst;
                        best_f = worst_f;
                    }
                }

                dp[j][b][best_f] = true;
            }
        }

        for (int f = 0; f < 8; ++f) {
            if (!dp[0][0][f]) continue;

            cout << "NY"[f >> 2] << "NY"[(f >> 1) & 1] << "NY"[f & 1] << endl;
        }
    }

    return 0;
}
