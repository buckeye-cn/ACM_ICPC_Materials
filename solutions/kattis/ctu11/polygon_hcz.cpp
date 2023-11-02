// https://open.kattis.com/problems/polygon

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define SCALE 200
#define SLOT 200

using namespace std;

bool intersect(
    long px1, long py1, long px2, long py2,
    long qx1, long qy1, long qx2, long qy2
) {
    long p12q1 = (qx1 - px1) * (py2 - py1) - (px2 - px1) * (qy1 - py1);
    long p12q2 = (qx2 - px1) * (py2 - py1) - (px2 - px1) * (qy2 - py1);

    if (p12q1 * p12q2 > 0) {
        return false;
    }

    long p1q12 = (px1 - qx1) * (qy2 - qy1) - (qx2 - qx1) * (py1 - qy1);
    long p2q12 = (px2 - qx1) * (qy2 - qy1) - (qx2 - qx1) * (py2 - qy1);

    if (p1q12 * p2q12 > 0) {
        return false;
    }

    return true;
}

long n;
long x[50000];
long y[50000];
long sx[50000];
long sy[50000];

long pxmap_tot[32000 / SCALE][32000 / SCALE];
long pxmap[32000 / SCALE][32000 / SCALE][SLOT];

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

            if (intersect(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l])) {
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
