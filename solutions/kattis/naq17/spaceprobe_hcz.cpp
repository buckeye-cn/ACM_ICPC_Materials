// https://open.kattis.com/problems/spaceprobe

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
long t1, t2;
long offset[20000];
long range[30000];
int cut_tot[2];
long cut[2][30000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k >> t1 >> t2;
    k = k * 2 + 2;

    for (int i = 0; i < n; ++i) {
        cin >> offset[i];
    }

    range[0] = 0;
    for (int i = 1; i < k - 1; ++i) {
        cin >> range[i];
    }
    range[k - 1] = 1l << 62;

    cut_tot[0] = 2;
    cut[0][0] = t1;
    cut[0][1] = t2;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < cut_tot[i & 1]; ++j) {
            cut[i & 1][j] += offset[i];
            if (i > 0) {
                cut[i & 1][j] -= offset[i - 1];
            }
        }

        cut_tot[(i & 1) ^ 1] = 0;

        int a = 0;
        int b = 0;
        int last = 0;

        while (a < cut_tot[i & 1] && b < k) {
            if (cut[i & 1][a] > range[b]) {
                ++b;

                // cout << (a & 1) << (b & 1) << ' ';
                if ((a & b & 1) != last) {
                    cut[(i & 1) ^ 1][cut_tot[(i & 1) ^ 1]++] = range[b - 1];
                    last = a & b & 1;
                }
            } else {
                ++a;

                // cout << (a & 1) << (b & 1) << ' ';
                if ((a & b & 1) != last) {
                    cut[(i & 1) ^ 1][cut_tot[(i & 1) ^ 1]++] = cut[i & 1][a - 1];
                    last = a & b & 1;
                }
            }
        }
        // cout << endl;

        for (int j = 0; j < cut_tot[(i & 1) ^ 1]; ++j) {
            // cout << cut[(i & 1) ^ 1][j] << ' ';
        }
        // cout << endl;
    }

    long tot = 0;

    for (int i = 0; i < cut_tot[n & 1]; ++i) {
        if (i & 1) {
            tot += cut[n & 1][i];
        } else {
            tot -= cut[n & 1][i];
        }
    }

    cout << tot / double(t2 - t1) << endl;

    return 0;
}
