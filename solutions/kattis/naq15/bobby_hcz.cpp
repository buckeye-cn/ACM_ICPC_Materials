// https://open.kattis.com/problems/bobby

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long pas[12][12];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    pas[0][0] = 1;
    for (int i = 1; i < 12; ++i) {
        pas[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            pas[i][j] = pas[i - 1][j - 1] + pas[i - 1][j];
        }
        pas[i][i] = 1;
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long r, s, w;
        int x, y;
        cin >> r >> s >> x >> y >> w;

        long pw = s - r + 1;
        long pl = r - 1;

        long aw[12];
        long al[12];
        aw[0] = 1;
        al[0] = 1;
        for (int j = 1; j <= y; ++j) {
            aw[j] = aw[j - 1] * pw;
            al[j] = al[j - 1] * pl;
        }

        long pw_tot = 0;
        long p_tot = 0;
        for (int j = 0; j <= y; ++j) {
            long p = pas[y][j] * aw[j] * al[y - j];
            p_tot += p;
            if (j >= x) {
                pw_tot += p;
            }
        }

        if (pw_tot * w > p_tot) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
