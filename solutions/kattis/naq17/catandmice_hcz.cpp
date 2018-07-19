// https://open.kattis.com/problems/catandmice

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int x[16];
int y[16];
int t[16];
double dist[16][16];
double cost[16][16];
double ret;

double dp[65536][16];

bool tryspeed(double speed) {
    double r_speed = 1 / speed;
    double r_ret = 1 / ret;

    for (int i = 0; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 1e30;
        }
    }

    for (int j = 0; j < n; ++j) {
        double tt = sqrt(x[j] * x[j] + y[j] * y[j]) * r_speed;

        if (tt < t[j]) {
            dp[1 << j][j] = tt;
        }
    }

    for (int iter = 1; iter < n; ++iter) {
        r_speed *= r_ret;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cost[i][j] = dist[i][j] * r_speed;
            }
        }

        for (int i = 0; i < 1 << n; ++i) {
            bool ok = true;
            int ki = i;
            for (int j = 0; j < iter; ++j) {
                if (!ki) ok = false;
                ki ^= (ki & -ki);
            }
            if (ki) ok = false;
            if (!ok) continue;

            for (int j = 0; j < n; ++j) {
                if (!(i & (1 << j))) continue;
                if (dp[i][j] == 1e30) continue;

                for (int k = 0; k < n; ++k) {
                    if (j == k) continue;
                    if (i & (1 << k)) continue;

                    double tt = dp[i][j] + cost[j][k];

                    if (tt < t[k]) {
                        dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], tt);
                    }

                    // cerr << iter << ' ' << i << ' ' << j << ':' << k << ' ' << tt << endl;
                }
            }
        }
    }

    int i = (1 << n) - 1;
    for (int j = 0; j < n; ++j) {
        if (dp[i][j] < t[j]) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(15);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> t[i];
    }

    cin >> ret;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double xx = x[i] - x[j];
            double yy = y[i] - y[j];

            dist[i][j] = sqrt(xx * xx + yy * yy);
        }
    }

    double speed_min = 0.001;
    double speed_max = 1000000;
    while (speed_max - speed_min > 0.001 || speed_max - speed_min > 0.001 * speed_min) {
        double speed = (speed_max + speed_min) / 2;

        if (tryspeed(speed)) {
            speed_max = speed;
        } else {
            speed_min = speed;
        }
    }

    cout << speed_min << endl;

    return 0;
}
