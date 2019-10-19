// https://open.kattis.com/problems/deletethis

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

    int nr, nc, n, m;
    cin >> nr >> nc >> n >> m;

    int r[n + m];
    int c[n + m];
    int s[n + m];

    for (int i = 0; i < n + m; ++i) {
        cin >> r[i] >> c[i];

        if (i < n) {
            s[i] = 1;
        } else {
            s[i] = -1;
        }

        for (int j = i - 1; j >= 0; --j) {
            if (c[j] < c[j + 1]) break;

            swap(r[j], r[j + 1]);
            swap(c[j], c[j + 1]);
            swap(s[j], s[j + 1]);
        }
    }

    int s_max = 0;

    for (int i = 0; i < n + m; ++i) {
        for (int j = 0; j < n + m; ++j) {
            if (r[i] > r[j] || r[j] > nr - 15) continue;

            int c_last = -1;
            int s_curr = 0;
            int s_sum = 0;

            for (int k = 0; k < n + m; ++k) {
                if (c[k] > nc - 9) continue;

                if (r[k] >= r[i] && r[k] <= r[j]) {
                    if (c_last != c[k]) {
                        c_last = c[k];

                        s_sum = max(s_sum + s_curr, 0);
                        s_max = max(s_max, s_sum);
                        s_curr = 0;
                    }

                    s_curr += s[k];
                }
            }

            s_sum = max(s_sum + s_curr, 0);
            s_max = max(s_max, s_sum);
        }
    }

    cout << n - s_max << endl;

    return 0;
}
