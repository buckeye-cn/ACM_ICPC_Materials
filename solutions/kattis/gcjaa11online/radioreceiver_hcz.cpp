// https://open.kattis.com/problems/radioreceiver

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int pp[1000];
int tt[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int n;
        cin >> n;

        set<pair<int, int>> s;

        for (int i = 0; i < n; ++i) {
            int p, t;
            cin >> p >> t;

            s.insert({t, p});
        }

        int i = 0;

        for (pair<int, int> p: s) {
            pp[i] = p.second;
            tt[i] = p.first;
            i += 1;
        }

        double l = 0;
        double r = 5e8;

        while (r - l > max(1e-9, 5e-10 * l)) {
            double m = (l + r) / 2;
            double pl = pp[0] - m;
            double pr = pp[0] + m;
            int t = tt[0];

            for (int i = 1; i < n; ++i) {
                pl = max(pl - tt[i] + t, pp[i] - m);
                pr = min(pr + tt[i] - t, pp[i] + m);
                t = tt[i];

                if (pl > pr) {
                    break;
                }
            }

            if (pl > pr) {
                l = m;
            } else {
                r = m;
            }
        }

        cout << "Case #" << n_case << ": " << l << endl;
    }

    return 0;
}
