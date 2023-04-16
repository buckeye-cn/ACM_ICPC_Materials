#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int m[26];

        for (int i = 0; i < 26; ++i) {
            cin >> m[i];
        }

        int n;
        cin >> n;

        bool ok = true;
        unordered_map<long, string> wm;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;

            long v = 1;

            for (char c: s) {
                v *= 10;
                v += m[c - 'A'];
            }

            string &sm = wm[v];

            if (sm == s) {
                // nothing
            } else if (sm.empty()) {
                sm = s;
            } else {
                ok = false;
            }
        }

        if (ok) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }

    return 0;
}
