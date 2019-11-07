// https://open.kattis.com/problems/cheeseifyouplease
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double w[50];
double p[50][50];
double t[50];

double p_sum[50];
double t_sum;

double amount[50];
double ap_sum[50];
double speed[50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            cin >> p[j][i];
            p[j][i] /= 100;
            p_sum[i] += p[j][i];
        }

        cin >> t[j];
        t_sum += t[j];
    }

    for (int iter = 0; iter < 200000; ++iter) {
        for (int i = 0; i < n; ++i) {
            ap_sum[i] = 0;

            for (int j = 0; j < m; ++j) {
                ap_sum[i] += amount[j] * p[j][i];
            }
        }

        double delta = 0.01 * exp((100000 - iter) * 0.0001);

        for (int j = 0; j < m; ++j) {
            double d = t[j] / t_sum;

            for (int i = 0; i < n; ++i) {
                if (ap_sum[i] > w[i]) {
                    d -= 6 * p[j][i] / p_sum[i];
                }
            }

            speed[j] = 0.95 * speed[j] + 0.05 * d;
            amount[j] += delta * speed[j];

            if (amount[j] < 0) {
                amount[j] = 0;
            }
        }
    }

    double result = 0;
    for (int j = 0; j < m; ++j) {
        result += amount[j] * t[j];
    }

    printf("%.2f\n", result);

    return 0;
}
