// https://open.kattis.com/problems/traintimetables

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int pa[1441];
int pb[1441];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        memset(pa, 0, sizeof(pa));
        memset(pb, 0, sizeof(pb));

        int tt, na, nb;
        cin >> tt >> na >> nb;

        for (int i = 0; i < na; ++i) {
            char c;
            int h1, m1, h2, m2;
            cin >> h1 >> c >> m1 >> h2 >> c >> m2;

            pa[h1 * 60 + m1] += 1;
            pb[h2 * 60 + m2 + tt] -= 1;
        }

        for (int i = 0; i < nb; ++i) {
            char c;
            int h1, m1, h2, m2;
            cin >> h1 >> c >> m1 >> h2 >> c >> m2;

            pb[h1 * 60 + m1] += 1;
            pa[h2 * 60 + m2 + tt] -= 1;
        }

        for (int i = 0; i < 1440; ++i) {
            pa[i + 1] += pa[i];
            pb[i + 1] += pb[i];
        }

        int a = 0;
        int b = 0;

        for (int i = 0; i <= 1440; ++i) {
            a = max(a, pa[i]);
            b = max(b, pb[i]);
        }

        cout << "Case #" << n_case << ": " << a << ' ' << b << endl;
    }

    return 0;
}
