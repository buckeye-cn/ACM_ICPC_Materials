// https://open.kattis.com/problems/removalgame

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int gcd[1001][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 1; i <= 1000; ++i) {
        int max = 1000 / i;

        for (int j = 1; j <= max; ++j) {
            for (int k = 1; k <= max; ++k) {
                gcd[i * j][i * k] = i;
            }
        }
    }

    while (true) {
        int tot;
        cin >> tot;

        if (!tot) break;

        int num[2 * tot];

        for (int i = 0; i < tot; ++i) {
            cin >> num[i];
            num[tot + i] = num[i];
        }

        int best[2 * tot][2 * tot];

        for (int i = 0; i < 2 * tot - 1; ++i) {
            best[i][i + 1] = 0;
        }

        for (int len = 2; len <= tot; ++len) {
            for (int i = 0; i < tot; ++i) {
                int val_best = 1 << 30;

                for (int j = i + 1; j < i + len; ++j) {
                    int val = best[i][j] + best[j][i + len] + gcd[num[i]][num[len < tot ? i + len : j]];

                    if (val_best > val) {
                        val_best = val;
                    }
                }

                best[i][i + len] = val_best;
                // cerr << len << ' ' << i << ' ' << val_best << endl;
            }
            for (int i = 0; i < tot - len; ++i) {
                best[i + tot][i + tot + len] = best[i][i + len];
            }
        }

        int result_best = 1 << 30;

        for (int i = 0; i < tot; ++i) {
            if (result_best > best[i][i + tot]) {
                result_best = best[i][i + tot];
            }
        }

        cout << result_best << endl;
    }

    return 0;
}
