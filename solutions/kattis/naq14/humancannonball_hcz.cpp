// https://open.kattis.com/problems/humancannonball

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int n;
double x_init;
double y_init;
double x[120];
double y[120];
double t[120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> x_init >> y_init >> x[0] >> y[0] >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i <= n; ++i) {
        t[i] = 0.2 * sqrt(sqr(x[i] - x_init) + sqr(y[i] - y_init));
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k) {
                double target = t[j] + 2
                    + 0.2 * abs(sqrt(sqr(x[j] - x[k]) + sqr(y[j] - y[k])) - 50);

                if (t[k] > target) {
                    t[k] = target;
                }
            }
        }
    }

    cout << t[0] << endl;

    return 0;
}
