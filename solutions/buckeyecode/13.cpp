#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

unordered_set<long> lcm[21][21];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    lcm[0][1].insert(1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            long g;
            cin >> g;

            long limit = 0x7fffffffffffffffl / g;

            for (long k: lcm[i - 1][j]) {
                bool ok = true;

                for (long k2: lcm[i - 1][j]) {
                    if (k > k2 && k % k2 == 0) {
                        ok = false;
                    }
                }

                if (ok) {
                    long p = k / gcd(g, k);

                    if (p <= limit) {
                        lcm[i][j].insert(g * p);
                    }
                }
            }

            for (long k: lcm[i][j - 1]) {
                bool ok = true;

                for (long k2: lcm[i][j - 1]) {
                    if (k > k2 && k % k2 == 0) {
                        ok = false;
                    }
                }

                if (ok) {
                    long p = k / gcd(g, k);

                    if (p <= limit) {
                        lcm[i][j].insert(g * p);
                    }
                }
            }
        }
    }

    long best = 0x7fffffffffffffffl;

    for (long k: lcm[n][n]) {
        best = min(best, k);
    }

    cout << best << endl;

    return 0;
}
