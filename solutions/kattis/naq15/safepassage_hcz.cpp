// https://open.kattis.com/problems/safepassage

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int load[15];
int min_cost_go[1 << 15];
int min_cost_ret[1 << 15];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> load[i];
    }

    for (int i = 0; i < 1 << n; ++i) {
        min_cost_go[i] = 1 << 30;
        min_cost_ret[i] = 1 << 30;
    }

    min_cost_ret[0] = 0;

    for (int iter = 0; true; ++iter) {
        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if (i & (1 << j)) continue;

                for (int k = j + 1; k < n; ++k) {
                    if (i & (1 << k)) continue;

                    min_cost_go[i | (1 << j) | (1 << k)] = min(
                        min_cost_go[i | (1 << j) | (1 << k)],
                        min_cost_ret[i] + max(load[j], load[k])
                    );
                }
            }
        }

        if (iter == n - 2) {
            cout << min_cost_go[(1 << n) - 1] << endl;

            return 0;
        }

        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (~(i | ~(1 << j))) continue;

                min_cost_ret[i & ~(1 << j)] = min(
                    min_cost_ret[i & ~(1 << j)],
                    min_cost_go[i] + load[j]
                );
            }
        }
    }
}
