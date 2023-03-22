// https://open.kattis.com/problems/outofcontext

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int tt[500];
int ll[500];
int rr[500];
bool init[500];
bool dp[51][51][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    init[0] = true;

    int n;
    cin >> n;

    int m = 0;
    char start = 0;

    for (int i = 0; i < n; ++i) {
        char to;
        string from;
        cin >> to;
        cin.get();
        cin.get();
        cin.get();
        cin.get();
        getline(cin, from);

        if (!start) {
            start = to;
        }

        if (from.empty()) {
            init[to] = true;
        } else {
            int prev = 0;

            for (int j = 0; j < from.size() - 1; ++j) {
                tt[m] = 128 + i * 10 + j;
                ll[m] = prev;
                rr[m] = from[j];
                m += 1;
                prev = 128 + i * 10 + j;
            }

            tt[m] = to;
            ll[m] = prev;
            rr[m] = from.back();
            m += 1;
        }
    }

    // for (int i = 0; i < m; ++i) {
    //     cerr << ll[i] << char(ll[i]) << ',' << char(rr[i]) << "->" << tt[i] << char(tt[i]) << endl;
    // }

    string line;

    while (getline(cin, line)) {
        int best_i = 0;
        int best_j = 0;

        for (int i = 0; i <= line.size(); ++i) {
            for (int j = line.size() - i; j >= 0; --j) {
                if (i == 0) {
                    for (int k = 0; k < 500; ++k) {
                        dp[j][j + i][k] = init[k];
                    }
                } else {
                    for (int k = 0; k < 500; ++k) {
                        dp[j][j + i][k] = false;
                    }

                    if (i == 1) {
                        dp[j][j + i][line[j]] = true;
                    }
                }

                for (int k = 0; k <= i; ++k) {
                    for (int s = 0; s < m; ++s) {
                        if (dp[j][j + k][ll[s]] && dp[j + k][j + i][rr[s]]) {
                            dp[j][j + i][tt[s]] = true;
                        }
                    }
                }

                for (int k = 0; k < m; ++k) {
                    for (int s = 0; s < m; ++s) {
                        if (dp[j][j][ll[s]] && dp[j][j + i][rr[s]]) {
                            dp[j][j + i][tt[s]] = true;
                        }

                        if (dp[j][j + i][ll[s]] && dp[j + i][j + i][rr[s]]) {
                            dp[j][j + i][tt[s]] = true;
                        }
                    }
                }

                for (int k = 0; k < 500; ++k) {
                    if (dp[j][j + i][start]) {
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        if (best_i) {
            for (int k = best_j; k < best_j + best_i; ++k) {
                cout << line[k];
            }

            cout << endl;
        } else {
            cout << "NONE" << endl;
        }
    }

    return 0;
}
