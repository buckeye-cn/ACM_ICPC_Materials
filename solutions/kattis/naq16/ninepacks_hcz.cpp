// https://open.kattis.com/problems/ninepacks

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int tot[2][102400];
int sum[2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 0; i < 2; ++i) {
        tot[i][0] = 1;

        int n;
        cin >> n;

        for (int j = 0; j < n; ++j) {
            int item;
            cin >> item;

            for (int k = sum[i]; k >= 0; --k) {
                if (tot[i][k]) {
                    if (tot[i][k + item]) {
                        tot[i][k + item] = min(tot[i][k + item], tot[i][k] + 1);
                    } else {
                        tot[i][k + item] = tot[i][k] + 1;
                    }
                }
            }

            sum[i] += item;
        }
    }

    int min_tot = 0;
    int s = min(sum[0], sum[1]);

    for (int i = 1; i <= s; ++i) {
        if (tot[0][i] && tot[1][i]) {
            if (min_tot) {
                min_tot = min(min_tot, tot[0][i] + tot[1][i]);
            } else {
                min_tot = tot[0][i] + tot[1][i];
            }
        }
    }

    if (min_tot) {
        cout << min_tot - 2 << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
