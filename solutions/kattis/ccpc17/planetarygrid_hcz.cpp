// https://open.kattis.com/problems/planetarygrid

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long a, b, x1, y1, x2, y2;
        cin >> a >> b >> x1 >> y1 >> x2 >> y2;

        long xm1 = x1 / a * a - a * (x1 < 0);
        long ym1 = y1 / b * b - b * (y1 < 0);
        long xm2 = x2 / a * a - a * (x2 < 0);
        long ym2 = y2 / b * b - b * (y2 < 0);

        pair<double, double> best {
            sqrt(sqr(x2 - x1) + sqr(y2 - y1)),
            sqrt(sqr(x2 - x1) + sqr(y2 - y1))
        };

        for (long xx = xm1; xx <= xm1 + a; xx += a) {
            best = min(best, {
                abs(x2 - xx) + abs(xx - x1),
                abs(x2 - xx) + abs(xx - x1) + abs(y2 - y1)
            });
        }

        for (long yy = ym1; yy <= ym1 + b; yy += b) {
            best = min(best, {
                abs(y2 - yy) + abs(yy - y1),
                abs(x2 - x1) + abs(y2 - yy) + abs(yy - y1)
            });
        }

        for (long xx1 = xm1; xx1 <= xm1 + a; xx1 += a) {
            for (long xx2 = xm2; xx2 <= xm2 + a; xx2 += a) {
                for (long yy1 = ym1; yy1 <= ym1 + b; yy1 += b) {
                    for (long yy2 = ym2; yy2 <= ym2 + b; yy2 += b) {
                        best = min(best, {
                            min(abs(xx1 - x1), abs(yy1 - y1)) + min(abs(xx2 - x2), abs(yy2 - y2)),
                            abs(x2 - xx2) + abs(xx2 - xx1) + abs(xx1 - x1) + abs(y2 - yy2) + abs(yy2 - yy1) + abs(yy1 - y1)
                        });
                    }
                }
            }
        }

        cout << round(best.second) << endl;
    }

    return 0;
}
