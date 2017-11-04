// https://open.kattis.com/problems/bubblytroubly

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

double pi = acos(-1);

int n, top;

double x[20];
double y[20];
int z[20];
double r[20];

double vol[20];

double flow[20][20];

void delta(
    double x1, double y1, double r1,
    double x2, double y2, double r2,
    double &lo, double &hi
) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double d_sqr = dx * dx + dy * dy;

    if (d_sqr >= (r1 + r2) * (r1 + r2)) {
        lo = 0;
        hi = 0;

        return;
    }

    if (d_sqr <= (r1 - r2) * (r1 - r2)) {
        if (r1 < r2) {
            lo = -pi;
            hi = pi;
        } else {
            lo = 0;
            hi = 0;
        }

        return;
    }

    double r_sqr_s = r1 * r1 + r2 * r2;
    double r_sqr_d = r1 * r1 - r2 * r2;
    double b_sqr = 2 * d_sqr * r_sqr_s - d_sqr * d_sqr - r_sqr_d * r_sqr_d;
    double b = sqrt(b_sqr);

    double cx1 = dx * d_sqr + dx * r_sqr_d + dy * b;
    double cy1 = dy * d_sqr + dy * r_sqr_d - dx * b;
    double cx2 = dx * d_sqr + dx * r_sqr_d - dy * b;
    double cy2 = dy * d_sqr + dy * r_sqr_d + dx * b;

    lo = atan2(cy1, cx1);
    hi = atan2(cy2, cx2);
}

void fill(double filled[], int i, double amount) {
    if (amount <= vol[i] - filled[i]) {
        filled[i] += amount;
    } else {
        amount -= vol[i] - filled[i];
        filled[i] = vol[i];

        for (int j = 0; j < n; ++j) {
            if (flow[i][j]) {
                fill(filled, j, flow[i][j] * amount);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> z[i] >> r[i] >> vol[i];
        if (z[top] < z[i]) {
            top = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        int range_tot = 1;
        double ranges[1000][2] = {{-pi, pi}};

        auto cut_range = [&](double lo, double hi) {
            double cut = 0;

            for (int i = 0; i < range_tot; ++i) {
                bool lo_left = lo <= ranges[i][0];
                bool lo_in = !lo_left && lo < ranges[i][1];
                bool hi_right = hi >= ranges[i][1];
                bool hi_in = !hi_right && hi > ranges[i][0];

                if (lo_left && hi_in) {
                    cut += hi - ranges[i][0];
                    ranges[i][0] = hi;
                } else if (lo_in && hi_right) {
                    cut += ranges[i][1] - lo;
                    ranges[i][1] = lo;
                } else if (lo_in && hi_in) {
                    cut += hi - lo;
                    ranges[range_tot][0] = hi;
                    ranges[range_tot][1] = ranges[i][1];
                    range_tot += 1;
                    ranges[i][1] = lo;
                } else if (lo_left && hi_right) {
                    cut += ranges[i][1] - ranges[i][0];
                    ranges[range_tot][0] = 0;
                    ranges[range_tot][1] = 0;
                }
            }

            return cut;
        };

        for (int z_drop = z[i] - 1; z_drop >= 0; --z_drop) {
            for (int j = 0; j < n; ++j) {
                if (z[j] != z_drop) continue;

                double lo, hi;
                delta(x[i], y[i], r[i], x[j], y[j], r[j], lo, hi);

                double cut = 0;
                if (lo < hi) {
                    cut = cut_range(lo, hi);
                } else if (lo > hi) {
                    cut = cut_range(-pi, hi) + cut_range(lo, pi);
                }

                flow[i][j] = cut / (2 * pi);
            }
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         if (flow[i][j]) {
    //             cout << i << ' ' << j << ' ' << flow[i][j] << endl;
    //         }
    //     }
    // }

    double lo = 0;
    double hi = 1e9;

    while (hi - lo > 1e-4) {
        double filled[20];
        for (int i = 0; i < n; ++i) {
            filled[i] = 0;
        }

        double mid = (lo + hi) / 2;

        fill(filled, top, mid);

        bool ok = true;

        for (int i = 0; i < n; ++i) {
            if (filled[i] < vol[i]) {
                ok = false;
            }
        }

        if (ok) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if (lo <= 1e8) {
        printf("%.2f\n", lo / 100);
    } else {
        printf("Invalid\n");
    }

    return 0;
}
