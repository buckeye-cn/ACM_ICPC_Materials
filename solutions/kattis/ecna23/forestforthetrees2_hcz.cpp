// https://open.kattis.com/problems/forestforthetrees2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int xt[5000];
int yt[5000];
int xs[1000];
int ys[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int nt, ns, r;
    cin >> nt >> ns >> r;

    for (int i = 0; i < nt; ++i) {
        cin >> xt[i] >> yt[i];
    }

    for (int i = 0; i < ns; ++i) {
        cin >> xs[i] >> ys[i];

        if (!xs[i] && !ys[i]) {
            cout << "Impossible" << endl;

            return 0;
        }
    }

    bool done = false;
    int x = 0;
    int y = 0;

    for (int d = 0; d < 4; ++d) {
        unordered_set<long> s;

        for (int i = 0; i < ns; ++i) {
            swap(xs[i], ys[i]);
            xs[i] = -xs[i];

            s.insert((xs[i] + 1000000l) * 1000000l + ys[i]);
        }

        for (int i = 0; i < nt; ++i) {
            int xx = xt[i] - xs[0];
            int yy = yt[i] - ys[0];
            int found = 0;

            for (int j = 0; j < nt; ++j) {
                if (abs(xt[j] - xx) + abs(yt[j] - yy) <= r) {
                    if (s.find((xt[j] - xx + 1000000l) * 1000000l + yt[j] - yy) == s.end()) {
                        found = 0;
                        break;
                    } else {
                        found += 1;
                    }
                }
            }

            if (found == ns) {
                // cerr << d << ' ' << i << ' ' << found << ' ' << xx << ':' << yy << endl;
                if (done) {
                    cout << "Ambiguous" << endl;

                    return 0;
                }

                done = true;
                x = xx;
                y = yy;
            }
        }
    }

    if (done) {
        cout << x << ' ' << y << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
