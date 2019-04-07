#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int res[5][1024];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int n, b, f;
        cin >> n >> b >> f;

        // cerr << n << ' ' << b << ' ' << f << endl;

        for (int i = 4; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                cout << "01"[(j >> i) & 1];
                // cerr << "01"[(j >> i) & 1];
            }
            cout << endl;
            // cerr << endl;

            string s;
            cin >> s;

            // cerr << s << endl;

            if (i < 4) {
                int cur = 0;
                for (int j = 0; j < n - b; ++j) {
                    while (!res[i + 1][cur]) {
                        cur += 1;
                    }
                    res[i + 1][cur] -= 1;

                    res[i][(cur << 1) + (s[j] - '0')] += 1;
                }
            } else {
                res[4][0] = 1;

                int cur = 0;
                for (int j = 1; j < n - b; ++j) {
                    if (s[j] != s[j - 1]) {
                        cur += 1;
                    }

                    res[4][cur] += 1;
                }
            }

            // for (int j = 0; j < n; ++j) {
            //     cerr << '\t' << res[i][j];
            // }
            // cerr << endl;
        }

        bool first = true;
        for (int i = 0; i < n; ++i) {
            if (res[0][i]) {
                res[0][i] -= 1;
            } else {
                if (first) {
                    first = false;
                } else {
                    cout << ' ';
                }

                cout << i;
            }
        }
        cout << endl;

        int result;
        cin >> result;
    }

    return 0;
}
