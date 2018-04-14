#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int run(const string &p) {
    int s = 1;
    int d = 0;

    for (char c: p) {
        if (c == 'C') {
            s *= 2;
        } else {
            d += s;
        }
    }

    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int d;
        string p;
        cin >> d >> p;

        int d1 = run(p);
        int diff = 0;
        while (d1 > d) {
            bool changed = false;

            for (int i = p.size() - 2; i >= 0; --i) {
                if (p[i + 1] == 'S' && p[i] == 'C') {
                    swap(p[i + 1], p[i]);

                    d1 = run(p);
                    diff += 1;
                    changed = true;
                    break;
                }
            }

            if (!changed) break;
        }

        if (d1 <= d) {
            cout << diff << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
