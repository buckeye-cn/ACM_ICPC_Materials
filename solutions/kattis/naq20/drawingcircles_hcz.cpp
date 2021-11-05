// https://open.kattis.com/problems/drawingcircles

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);

using namespace std;

double x[2000];
double y[2000];
double r[2000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    double rsum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> r[i];
        rsum += r[i];
    }

    double total = 0;

    for (int i = 0; i < n; ++i) {
        map<double, int> cut;

        cut[-PI] = 1;
        cut[PI] = -1;

        double eps = 1e-10 * rsum / r[i];

        for (int j = i + 1; j < n; ++j) {
            if (sqr(x[j] - x[i]) + sqr(y[j] - y[i]) >= sqr(r[j] + r[i])) {
                // nothing
            } else if (sqr(x[j] - x[i]) + sqr(y[j] - y[i]) <= sqr(r[j] - r[i])) {
                if (r[i] <= r[j]) {
                    cut.clear();

                    break;
                }
            } else {
                double a = atan2(y[j] - y[i], x[j] - x[i]);
                double da_l = 0;
                double da_r = PI;

                while (da_r - da_l > eps) {
                    double da_m = (da_r + da_l) / 2;
                    double xx = x[i] + r[i] * cos(a + da_m);
                    double yy = y[i] + r[i] * sin(a + da_m);

                    if (sqr(xx - x[j]) + sqr(yy - y[j]) < sqr(r[j])) {
                        da_l = da_m;
                    } else {
                        da_r = da_m;
                    }
                }

                if (a - da_r < -PI) {
                    cut[a - da_r + 2 * PI] -= 1;
                    cut[PI] += 1;
                    cut[-PI] -= 1;
                } else {
                    cut[a - da_r] -= 1;
                }

                if (a + da_r > PI) {
                    cut[PI] += 1;
                    cut[-PI] -= 1;
                    cut[a + da_r - 2 * PI] += 1;
                } else {
                    cut[a + da_r] += 1;
                }
            }
        }

        double pos = -PI;
        int cut_sum = 0;

        for (pair<double, int> p: cut) {
            if (cut_sum > 0) {
                total += (p.first - pos) * r[i];
            }

            pos = p.first;
            cut_sum += p.second;
        }
    }

    cout << total << endl;

    return 0;
}
