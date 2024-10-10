// https://open.kattis.com/problems/balatro

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int a[200000];
long cost[30][200001];
long prev_cost[200001];
int sep_count[30];
int sep[30][200001];
long result[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, kk;
    cin >> n >> kk;

    int count_a = 0;
    int count_m = 0;

    sep_count[0] = 1;

    auto flush_a = [&](int level) {
        memcpy(prev_cost, cost[level], sizeof(prev_cost));
        int pos_r = n + 1;

        for (int i = sep_count[level] - 1; i >= 0; --i) {
            int pos_l = sep[level][i];
            int pos_a = 0;
            long curr = prev_cost[pos_l];

            for (int j = pos_l + 1; j <= n; ++j) {
                long d = prev_cost[pos_l + 1] - prev_cost[pos_l];

                if (pos_l + 1 < pos_r && pos_a < count_a) {
                    if (d > -a[pos_a]) {
                        curr += d;
                        pos_l += 1;
                    } else {
                        curr -= a[pos_a];
                        pos_a += 1;
                    }
                } else if (pos_l + 1 < pos_r) {
                    curr += d;
                    pos_l += 1;
                } else if (pos_a < count_a) {
                    curr -= a[pos_a];
                    pos_a += 1;
                } else {
                    break;
                }

                cost[level][j] = max(cost[level][j], curr);
            }

            pos_r = sep[level][i];
        }
    };

    for (int i = 0; i < n; ++i) {
        char s;
        int v;
        cin >> s >> v;

        if (s == 'a') {
            a[count_a++] = -v;
        } else {
            count_m += 1;
            sort(a, a + count_a);

            for (int j = 0; j <= kk && j < count_m; ++j) {
                flush_a(j);
            }

            count_a = 0;

            for (int j = min(kk, count_m); j > 0; --j) {
                sep_count[j] = 1;

                for (int k = 1; k <= n; ++k) {
                    cost[j][k] = max(cost[j][k], cost[j - 1][k] * v);
                }

                for (int k = 2; k <= n; ++k) {
                    if (cost[j][k - 1] * 2 < cost[j][k - 2] + cost[j][k]) {
                        sep[j][sep_count[j]++] = k;
                    }
                }
            }
        }
    }

    sort(a, a + count_a);

    for (int i = 0; i <= kk && i <= count_m; ++i) {
        flush_a(i);

        for (int j = 0; j <= n - count_m; ++j) {
            result[i + j] = max(result[i + j], cost[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        result[i] = max(result[i - 1], result[i]);
        cout << result[i] << endl;
    }

    return 0;
}
