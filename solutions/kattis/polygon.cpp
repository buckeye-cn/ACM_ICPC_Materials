// https://open.kattis.com/problems/polygon

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

#define sign(x) ((x) > 0 ? 1 : (x) < 0 ? -1 : 0)

long n;
long x[50000];
long y[50000];
long sx[50000];
long sy[50000];

#define SCALE 160
#define SLOT 1000
long pxmap_tot[32000 / SCALE][32000 / SCALE];
long pxmap[32000 / SCALE][32000 / SCALE][SLOT];

bool cross(long x1, long y1, long x2, long y2, long x3, long y3, long x4, long y4) {
    long s123 = (x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1);
    long s124 = (x4 - x1) * (y2 - y1) - (x2 - x1) * (y4 - y1);

    if (s123 * s124 > 0) {
        return false;
    }

    long s134 = (x1 - x3) * (y4 - y3) - (x4 - x3) * (y1 - y3);
    long s234 = (x2 - x3) * (y4 - y3) - (x4 - x3) * (y2 - y3);

    if (s134 * s234 > 0) {
        return false;
    }

    return true;
}

bool draw(long i, long j) {
    long ux = sx[j] > sx[i] ? 1 : -1;
    long uy = sy[j] > sy[i] ? 1 : -1;

    long xx = sx[i];
    long yy = sy[i];
    long o = 0;
    long ox = abs(sy[j] - sy[i]);
    long oy = abs(sx[j] - sx[i]);

    bool tested[i];
    memset(tested, 0, sizeof(tested));

    if (i > 0) tested[i - 1] = true;
    if (i == n - 1) tested[0] = true;

    while (true) {
        for (long kk = 0; kk < pxmap_tot[xx][yy]; ++kk) {
            long k = pxmap[xx][yy][kk];
            long l = k + 1;

            if (tested[k]) continue;
            tested[k] = true;

            if (cross(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l])) {
                return true;
            }
        }

        pxmap[xx][yy][pxmap_tot[xx][yy]++] = i;

        if (xx == sx[j] && yy == sy[j]) break;

        long o1 = o + ox;
        long o2 = o - oy;

        if (abs(o1) < abs(o2)) {
            xx += ux;
            o = o1;
        } else {
            yy += uy;
            o = o2;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        cin >> n;

        if (n == 0) {
            return 0;
        }

        for (long i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
            sx[i] = x[i] / SCALE;
            sy[i] = y[i] / SCALE;
        }

        memset(pxmap_tot, 0, sizeof(pxmap_tot));

        bool result = true;

        for (long i = 0; i < n - 1; ++i) {
            if (draw(i, i + 1)) {
                result = false;
                goto out;
            }
        }
        if (draw(n - 1, 0)) {
            result = false;
            goto out;
        }

        out:
        cout << (result ? "YES" : "NO") << endl;
    }
}
