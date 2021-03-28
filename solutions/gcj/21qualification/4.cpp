#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string msort(string all) {
    string l;
    string m;
    string r;

    for (int i = 2; i < all.size(); ++i) {
        cout << int(all[0]) << ' ' << int(all[1]) << ' ' << int(all[i]) << endl;

        int res;
        cin >> res;

        if (res == all[0]) {
            l.push_back(all[i]);
        } else if (res == all[1]) {
            r.push_back(all[i]);
        } else {
            m.push_back(all[i]);
        }
    }

    if (l.size() >= 2) {
        l = msort(l);

        cout << int(l[0]) << ' ' << int(l[1]) << ' ' << int(all[0]) << endl;

        int res;
        cin >> res;

        if (res == l[0]) {
            l = string(l.rbegin(), l.rend());
        }
    }

    if (m.size() >= 2) {
        m = msort(m);

        cout << int(m[0]) << ' ' << int(m[1]) << ' ' << int(all[0]) << endl;

        int res;
        cin >> res;

        if (res == m[1]) {
            m = string(m.rbegin(), m.rend());
        }
    }

    if (r.size() >= 2) {
        r = msort(r);

        cout << int(r[0]) << ' ' << int(r[1]) << ' ' << int(all[0]) << endl;

        int res;
        cin >> res;

        if (res == r[1]) {
            r = string(r.rbegin(), r.rend());
        }
    }

    return l + all[0] + m + all[1] + r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t, n, tmp;
    cin >> t >> n >> tmp;

    for (int n_case = 1; n_case <= t; ++n_case) {
        string all;

        for (int i = 0; i < n; ++i) {
            all.push_back(i + 1);
        }

        all = msort(all);

        for (int i = 0; i < all.size(); ++i) {
            cout << int(all[i]);

            if (i < all.size() - 1) {
                cout << ' ';
            } else {
                cout << endl;
            }
        }

        cin >> tmp;
    }

    return 0;
}
