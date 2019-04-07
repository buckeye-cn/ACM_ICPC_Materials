#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int n, b, f;
        cin >> n >> b >> f;

        int res[n - b];
        memset(res, 0, sizeof(res));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << char('0' + ((j >> i) & 1));
            }
            cout << endl;

            for (int j = 0; j < n - b; ++j) {
                char c;
                cin >> c;

                res[j] |= (c - '0') << i;
            }
        }

        // for (int i = 0; i < n - b; ++i) {
        //     cerr << '\t' << res[i];
        // }
        // cerr << endl;

        bool first = true;
        int pos = 0;

        for (int i = 0; i < n; ++i) {
            if (res[pos] == (i & 0xf)) {
                pos += 1;
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
