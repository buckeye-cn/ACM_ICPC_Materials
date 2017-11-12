// https://open.kattis.com/problems/units

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string unit[12];
int conv[12][12];
int i_dict[12];
int k_dict[12];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n;
        cin >> n;

        if (n == 0) {
            return 0;
        }

        memset(conv, 0, sizeof(conv));

        for (int i = 0; i < n; ++i) {
            cin >> unit[i];
        }

        for (int i = 0; i < n - 1; ++i) {
            string a, b;
            int ia, ib, k;
            char eq;
            cin >> a >> eq >> k >> b;

            for (int j = 0; j < n; ++j) {
                if (unit[j] == a) {
                    ia = j;
                }
                if (unit[j] == b) {
                    ib = j;
                }
            }

            conv[ib][ia] = k;
        }

        // slow but works
        for (int iter = 0; iter < n; ++iter)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;

                for (int k = 0; k < n; ++k) {
                    if (i == k || j == k) continue;

                    if (conv[i][k] && conv[k][j]) {
                        conv[i][j] = conv[i][k] * conv[k][j];
                    } else if (conv[i][k] && conv[j][k]) {
                        if (conv[i][k] % conv[j][k] == 0) {
                            conv[i][j] = conv[i][k] / conv[j][k];
                        } else if (conv[j][k] % conv[i][k] == 0) {
                            conv[j][i] = conv[j][k] / conv[i][k];
                        }
                    } else if (conv[k][i] && conv[k][j]) {
                        if (conv[k][j] % conv[k][i] == 0) {
                            conv[i][j] = conv[k][j] / conv[k][i];
                        } else if (conv[k][i] % conv[k][j] == 0) {
                            conv[j][i] = conv[k][i] / conv[k][j];
                        }
                    } else if (conv[k][i] && conv[j][k]) {
                        conv[j][i] = conv[j][k] * conv[k][i];
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            int tot = 0;
            int k = 1;

            for (int j = 0; j < n; ++j) {
                if (conv[i][j]) {
                    ++tot;

                    if (k < conv[i][j]) {
                        k = conv[i][j];
                    }
                }
            }

            i_dict[tot] = i;
            k_dict[tot] = k;

            // cout << unit[i] << ' ' << tot << ' ' << k << endl;
        }

        for (int i = 0; i < n; ++i) {
            if (i) {
                cout << " = ";
            }
            cout << k_dict[i] << unit[i_dict[i]];
        }
        cout << endl;
    }
}
