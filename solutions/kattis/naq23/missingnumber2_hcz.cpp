// https://open.kattis.com/problems/missingnumber2

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

    while (t--) {
        string s;
        cin >> s;

        int n = 0;
        int ans[10];

        for (int i = 1; i <= 5; ++i) {
            int pos = 0;
            int v0 = 0;

            while (pos < i) {
                v0 *= 10;
                v0 += s[pos++] - '0';
            }

            int v = v0 + 1;
            int m = 0;

            while (pos < s.size()) {
                string vs = to_string(v);

                if (s.compare(pos, vs.size(), vs)) {
                    if (m) break;

                    m = v;
                } else {
                    pos += vs.size();
                }

                v += 1;
            }

            if (pos == s.size()) {
                if (m) {
                    ans[n++] = m;
                } else {
                    if (v0 > 1) {
                        ans[n++] = v0 - 1;
                    }

                    if (v <= 99999) {
                        ans[n++] = v;
                    }
                }
            }
        }

        cout << n << endl;

        for (int i = 0; i < n; ++i) {
            if (i) {
                cout << ' ';
            }

            cout << ans[i];
        }

        cout << endl;
    }

    return 0;
}
