#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int v[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        cin >> n;

        bool ok = true;
        int nn = 0;
        unordered_set<int> s;

        for (int i = 0; i < n; ++i) {
            cin >> v[nn];

            if (nn && v[nn] == v[nn - 1]) {
                // nothing
            } else if (s.find(v[nn]) == s.end()) {
                s.insert(v[nn]);
                nn += 1;
            } else {
                ok = false;
            }
        }

        if (ok) {
            for (int i = 0; i < nn; ++i) {
                if (i) {
                    cout << ' ';
                }

                cout << v[i];
            }

            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
