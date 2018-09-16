// https://open.kattis.com/problems/yesyes

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

__int128 shift_base = 1;

int n[2];
int state_tot[2][128];
__int128 state_map[2][128];
__int128 b[2][128];
__int128 w[2][128];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n[0] >> n[1];

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j <= n[i] + 1; ++j) {
            state_tot[i][j] = 1;
            state_map[i][j] = 1;
        }
        for (int j = 1; j <= n[i]; ++j) {
            int count;
            cin >> count;

            for (int k = 0; k < count; ++k) {
                int black;
                cin >> black;

                state_tot[i][j] += black;
                state_map[i][j] |= shift_base << state_tot[i][j];
                state_tot[i][j] += 1;
            }
        }
    }

    memset(b, -1, sizeof(b));
    memset(w, -1, sizeof(w));

    for (int iter = 0; iter < 20; ++iter) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= n[i]; ++j) {
                __int128 line_b[128][128];
                __int128 line_w[128][128];
                bool ok[128][128];

                memset(line_b, 0, sizeof(line_b));
                memset(line_w, 0, sizeof(line_w));
                memset(ok, 0, sizeof(ok));

                ok[0][0] = true;

                for (int k = 0; k <= n[i ^ 1] + 1; ++k) {
                    for (int state = 0; state < state_tot[i][j]; ++state) {
                        if (ok[k][state]) {
                            // cerr << k << ' ' << state << endl;
                            if (state_map[i][j] & (shift_base << state)) {
                                if (w[i ^ 1][k] & (shift_base << j)) {
                                    line_b[k + 1][state] |= line_b[k][state];
                                    line_w[k + 1][state] |= line_w[k][state] | (shift_base << k);
                                    ok[k + 1][state] = true;
                                    line_b[k + 1][state + 1] |= line_b[k][state];
                                    line_w[k + 1][state + 1] |= line_w[k][state] | (shift_base << k);
                                    ok[k + 1][state + 1] = true;
                                }
                            } else {
                                if (b[i ^ 1][k] & (shift_base << j)) {
                                    line_b[k + 1][state + 1] |= line_b[k][state] | (shift_base << k);
                                    line_w[k + 1][state + 1] |= line_w[k][state];
                                    ok[k + 1][state + 1] = true;
                                }
                            }
                        }
                    }
                }

                // for (int k = 0; k <= n[i ^ 1] + 1; ++k) {
                //     cerr << ((line_b[n[i ^ 1] + 2][state_tot[i][j]] & shift_base << k) > 0);
                // }
                // cerr << endl;
                // for (int k = 0; k <= n[i ^ 1] + 1; ++k) {
                //     cerr << ((line_w[n[i ^ 1] + 2][state_tot[i][j]] & shift_base << k) > 0);
                // }
                // cerr << endl << endl;

                b[i][j] = line_b[n[i ^ 1] + 2][state_tot[i][j]];
                w[i][j] = line_w[n[i ^ 1] + 2][state_tot[i][j]];
            }
        }
    }

    for (int i = 0; i < 1; ++i) {
        for (int j = 1; j <= n[i]; ++j) {
            for (int k = 1; k <= n[i ^ 1]; ++k) {
                bool has_b = b[i ^ 1][k] & (shift_base << j) && b[i][j] & (shift_base << k);
                bool has_w = w[i ^ 1][k] & (shift_base << j) && w[i][j] & (shift_base << k);

                if (has_b && has_w) {
                    cout << '?';
                } else if (has_b) {
                    cout << 'X';
                } else if (has_w) {
                    cout << '.';
                } else {
                    // never reach
                    cout << '@';
                }
            }
            cout << endl;
        }
    }

    return 0;
}
