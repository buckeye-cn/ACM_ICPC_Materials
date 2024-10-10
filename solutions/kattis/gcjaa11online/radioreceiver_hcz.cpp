// https://open.kattis.com/problems/radioreceiver

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

pair<int, int> tp[1000];

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

        for (int i = 0; i < n; ++i) {
            cin >> tp[i].second >> tp[i].first;
        }

        sort(tp, tp + n);

        double l = 0;
        double r = 5e8;

        while (r - l > max(1e-9, 5e-10 * l)) {
            double m = (l + r) / 2;
            double pl = tp[0].second - m;
            double pr = tp[0].second + m;
            int t = tp[0].first;

            for (int i = 1; i < n; ++i) {
                pl = max(pl - tp[i].first + t, tp[i].second - m);
                pr = min(pr + tp[i].first - t, tp[i].second + m);
                t = tp[i].first;

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

        cout << l << endl;
    }

    return 0;
}
