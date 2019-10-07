// https://open.kattis.com/problems/craters

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
double x[200];
double y[200];
double r[200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> r[i];
        r[i] += 10;
    }

    int first = 0;
    double first_xx = -INFINITY;

    for (int i = 0; i < n; ++i) {
        double xx = x[i] + r[i];
        if (first_xx < xx) {
            first = i;
            first_xx = xx;
        }
    }

    int second = -1;
    int now = first;
    double now_base = 1;
    double now_tx = 0;
    double now_ty = 1;
    double result = 0;

    while (true) {
        int next = -1;
        double next_c = -INFINITY;
        double next_base = NAN;
        double next_tx = NAN;
        double next_ty = NAN;

        for (int i = 0; i < n; ++i) {
            if (i == now) continue;

            double dx = x[i] - x[now];
            double dy = y[i] - y[now];
            double dr = r[i] - r[now];

            double s2 = sqr(dx) + sqr(dy);
            double l = sqrt(s2 - sqr(dr));
            double base = 1 / l;

            double tx = dx - dr * (dx * dr - dy * l) / s2;
            double ty = dy - dr * (dy * dr + dx * l) / s2;
            // double tx = (dx * sqr(l) + dy * dr * l) / s2;
            // double ty = (dy * sqr(l) - dx * dr * l) / s2;

            if (now_tx * ty < now_ty * tx) continue;

            double c = (now_tx * tx + now_ty * ty) * now_base * base;
            if (next_c < c) {
                next = i;
                next_c = c;
                next_base = base;
                next_tx = tx;
                next_ty = ty;
            }

            // cerr << i << ':' << c << '\t' << dx << ',' << dy << ',' << dr << '\t' << tx << ',' << ty << '\n';
        }

        // cerr << now << ',' << next << endl;

        if (second == -1) {
            if (next == -1) {
                // one large circle
                cout << 2 * acos(-1) * r[first] << endl;

                return 0;
            } else {
                second = next;
            }
        } else {
            result += sqrt(sqr(next_tx) + sqr(next_ty));
            result += acos(next_c) * r[now];

            if (now == first && next == second) {
                break;
            }
        }

        now = next;
        now_base = next_base;
        now_tx = next_tx;
        now_ty = next_ty;
    }

    cout << result << endl;

    return 0;
}
