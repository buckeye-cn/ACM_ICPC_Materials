// https://open.kattis.com/problems/probedroids

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long buf_y[1000000];
long buf_x[1000000];
int tot;

long gcd(long y, long x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

long count_points(long n, long m, long range) {
    if (range < n) {
        return (range * m - 1 + gcd(range - 1, m - 1)) / 2;
    } else if (range < n + m) {
        return (range * n - (n - m) * n - 1 + gcd(n + m - range - 1, n - 1)) / 2;
    } else {
        return n * m;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n, m, index;
    cin >> n >> m >> index;

    for (long i = 0; i < index; ++i) {
        long index;
        cin >> index;

        if (index < m) {
            cout << "1 " << index + 1 << endl;
        } else if (index >= n * (m - 1) + 1) {
            cout << index - n * (m - 1) + 1 << " 1" << endl;
        } else {
            long lo = 0;

            for (long b = 1l << 20; b; b >>= 1) {
                if (count_points(n, m, lo + b) < index) {
                    lo += b;
                }
            }

            index -= count_points(n, m, lo);

            long bound_y;
            long bound_x;
            if (lo < n) {
                bound_y = lo - 1;
                bound_x = m - 1;
            } else {
                bound_y = n - 1;
                bound_x = n + m - lo - 1;
            }

            long y1 = 0;
            long x1 = 1;

            while (
                y1 + 1 < n
                && x1 < m
                && (y1 + 1) * bound_x <= x1 * bound_y
            ) {
                y1 += 1;
            }

            buf_y[0] = 1;
            buf_x[0] = 0;
            tot = 1;

            while (tot) {
                long y = y1 + buf_y[tot - 1];
                long x = x1 + buf_x[tot - 1];

                if (y >= n || x >= m) {
                    if (y1 * bound_x > x1 * bound_y) {
                        long count = min((n - 1) / y1, (m - 1) / x1);

                        if (count > index - 1) {
                            cout << y1 * index + 1 << ' ' << x1 * index + 1 << endl;
                            break;
                        }

                        index -= count;
                    }

                    y1 = buf_y[tot - 1];
                    x1 = buf_x[tot - 1];
                    tot -= 1;
                } else if (y * bound_x > x * bound_y) {
                    buf_y[tot] = y;
                    buf_x[tot] = x;
                    tot += 1;
                } else {
                    y1 = y;
                    x1 = x;
                }
            }
        }
    }

    return 0;
}
