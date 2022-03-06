// https://open.kattis.com/problems/growingsomeoobleck

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

double x[100];
double y[100];
double rad[100];
double spd[100];
bool done[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> rad[i] >> spd[i];
    }

    int nn = n;

    while (true) {
        double best_t = 1e9;
        int best_i = -1;

        for (int i = 0; i < n; ++i) {
            if (done[i]) continue;

            for (int j = 0; j < i; ++j) {
                if (done[j]) continue;

                double t = (sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j])) - rad[i] - rad[j]) / (spd[i] + spd[j]);

                if (best_t > t) {
                    best_t = t;
                    best_i = i;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            rad[i] += spd[i] * best_t;
        }

        while (true) {
            int tot = 1;
            double sum_x = x[best_i];
            double sum_y = y[best_i];
            double sum_sqr = sqr(rad[best_i]);
            double max_spd = spd[best_i];

            for (int i = 0; i < n; ++i) {
                if (done[i] || i == best_i) continue;

                if (sqr(x[i] - x[best_i]) + sqr(y[i] - y[best_i]) < sqr(rad[i] + rad[best_i] + 1e-6)) {
                    tot += 1;
                    sum_x += x[i];
                    sum_y += y[i];
                    sum_sqr += sqr(rad[i]);
                    max_spd = max(max_spd, spd[i]);

                    done[i] = true;
                    nn -= 1;
                }
            }

            if (tot > 1) {
                x[best_i] = sum_x / tot;
                y[best_i] = sum_y / tot;
                rad[best_i] = sqrt(sum_sqr);
                spd[best_i] = max_spd;
            } else {
                break;
            }
        }

        if (nn == 1) {
            cout << x[best_i] << ' ' << y[best_i] << endl;
            cout << rad[best_i] << endl;

            return 0;
        }
    }
}
