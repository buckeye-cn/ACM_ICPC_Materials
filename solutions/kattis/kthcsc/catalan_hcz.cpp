// https://open.kattis.com/problems/catalan

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 10000000000000000l

using namespace std;

long v[1000][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        v[i][0] = 1;

        for (int j = 2; j <= x; ++j) {
            v[i][0] *= long(x + j);

            for (int k = 0; k < 999; ++k) {
                v[i][k + 1] *= long(x + j);
                v[i][k + 1] += v[i][k] / MOD;
                v[i][k] %= MOD;
            }
        }

        for (int j = 2; j <= x; ++j) {
            for (int k = 999; k >= 0; --k) {
                v[i][k] += v[i][k + 1] % long(j) * MOD;
                v[i][k + 1] /= long(j);
            }

            v[i][0] /= long(j);
        }

        for (int k = 1000; k >= 0; --k) {
            if (v[i][k]) {
                printf("%ld", v[i][k]);

                for (--k; k >= 0; --k) {
                    printf("%010ld", v[i][k]);
                }
            }
        }

        printf("\n");
    }

    return 0;
}
