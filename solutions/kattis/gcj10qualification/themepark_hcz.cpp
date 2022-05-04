// https://open.kattis.com/problems/themepark

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long g[1000];
long s[1000];
int jmp[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    cin.get();

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int r, k, n;
        cin >> r >> k >> n;

        for (int i = 0; i < n; ++i) {
            cin >> g[i];
            s[i] = 0;
            jmp[i] = 0;
        }

        int p = 0;

        for (int i = 0; i < n; ++i) {
            if (i) {
                s[i] = s[i - 1] - g[i - 1];
            }

            while (s[i] + g[p] <= k) {
                s[i] += g[p];
                p = (p + 1) % n;

                if (p == i) break;
            }

            jmp[i] = p;
        }

        int l = n;
        int p1 = 0;
        int p2 = 0;
        long s1 = 0;
        long s2 = 0;

        for (int i = 0; i < n; ++i) {
            s1 += s[p1];
            s2 += s[p2];
            s2 += s[jmp[p2]];
            p1 = jmp[p1];
            p2 = jmp[jmp[p2]];

            if (p1 == p2) {
                l = i + 1;
                break;
            }
        }

        int bound = min(l + r % l, r);
        long ss = 0;

        p = 0;

        for (int i = 0; i < bound; ++i) {
            ss += s[p];
            p = jmp[p];
        }

        ss += (r - bound) / l * (s2 - s1);

        cout << ss << endl;
    }

    return 0;
}
