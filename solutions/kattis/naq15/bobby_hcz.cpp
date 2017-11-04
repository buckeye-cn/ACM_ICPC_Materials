// https://open.kattis.com/problems/bobby

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long pas[11][11];
long pwr[21][11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    pas[0][0] = 1;
    for (int i = 1; i <= 10; ++i) {
        pas[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            pas[i][j] = pas[i - 1][j - 1] + pas[i - 1][j];
        }
        pas[i][i] = 1;
    }

    for (int i = 0; i <= 20; ++i) {
        pwr[i][0] = 1;
        for (int j = 1; j <= 10; ++j) {
            pwr[i][j] = pwr[i][j - 1] * i;
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int r, s, x, y, w;
        cin >> r >> s >> x >> y >> w;

        int pw = s - r + 1;
        int pl = r - 1;

        long pw_tot = 0;
        long p_tot = 0;
        for (int j = 0; j <= y; ++j) {
            long p = pas[y][j] * pwr[pw][j] * pwr[pl][y - j];
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
