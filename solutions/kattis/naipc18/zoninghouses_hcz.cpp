// https://open.kattis.com/problems/zoninghouses

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

#define XMIN1 0
#define XMAX1 1
#define YMIN1 2
#define YMAX1 3
#define XMIN2 4
#define XMAX2 5
#define YMIN2 6
#define YMAX2 7

int n, q;
int x[100002];
int y[100002];
int d[17][100000][8];

void merge(int *d1, int *d2, int *dd) {
    int b1, n1, b2;

    b1 = x[d1[XMIN1]] < x[d2[XMIN1]] ? d1[XMIN1] : d2[XMIN1];
    n1 = x[d1[XMIN1]] < x[d2[XMIN1]] ? d2[XMIN1] : d1[XMIN1];
    b2 = x[d1[XMIN2]] < x[d2[XMIN2]] ? d1[XMIN2] : d2[XMIN2];
    b2 = x[b2] < x[n1] ? b2 : n1;
    dd[XMIN1] = b1;
    dd[XMIN2] = b2;

    b1 = x[d1[XMAX1]] > x[d2[XMAX1]] ? d1[XMAX1] : d2[XMAX1];
    n1 = x[d1[XMAX1]] > x[d2[XMAX1]] ? d2[XMAX1] : d1[XMAX1];
    b2 = x[d1[XMAX2]] > x[d2[XMAX2]] ? d1[XMAX2] : d2[XMAX2];
    b2 = x[b2] > x[n1] ? b2 : n1;
    dd[XMAX1] = b1;
    dd[XMAX2] = b2;

    b1 = y[d1[YMIN1]] < y[d2[YMIN1]] ? d1[YMIN1] : d2[YMIN1];
    n1 = y[d1[YMIN1]] < y[d2[YMIN1]] ? d2[YMIN1] : d1[YMIN1];
    b2 = y[d1[YMIN2]] < y[d2[YMIN2]] ? d1[YMIN2] : d2[YMIN2];
    b2 = y[b2] < y[n1] ? b2 : n1;
    dd[YMIN1] = b1;
    dd[YMIN2] = b2;

    b1 = y[d1[YMAX1]] > y[d2[YMAX1]] ? d1[YMAX1] : d2[YMAX1];
    n1 = y[d1[YMAX1]] > y[d2[YMAX1]] ? d2[YMAX1] : d1[YMAX1];
    b2 = y[d1[YMAX2]] > y[d2[YMAX2]] ? d1[YMAX2] : d2[YMAX2];
    b2 = y[b2] > y[n1] ? b2 : n1;
    dd[YMAX1] = b1;
    dd[YMAX2] = b2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> q;

    for (int j = 0; j < n; ++j) {
        cin >> x[j] >> y[j];

        d[0][j][XMIN1] = j;
        d[0][j][XMAX1] = j;
        d[0][j][YMIN1] = j;
        d[0][j][YMAX1] = j;
        d[0][j][XMIN2] = 100000;
        d[0][j][XMAX2] = 100001;
        d[0][j][YMIN2] = 100000;
        d[0][j][YMAX2] = 100001;
    }

    x[100000] = 1000000000;
    y[100000] = 1000000000;
    x[100001] = -(1000000000);
    y[100001] = -(1000000000);

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j + 1 < n >> i; j += 2) {
            merge(d[i][j], d[i][j + 1], d[i + 1][j >> 1]);
        }
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;

        l -= 1;

        int split = -1;
        int lm = -1;
        int rm = -1;

        for (int i = 16; i >= 0; --i) {
            if ((l >> i) != (r >> i)) {
                split = i;

                lm = rm = r >> i << i;

                break;
            }
        }

        int dd[8] = {100000, 100001, 100000, 100001, 100000, 100001, 100000, 100001};

        for (int i = split; i >= 0; --i) {
            if (lm - (1 << i) >= l) {
                // cout << 'l' << lm - (1 << i) << '-' << lm << endl;
                merge(dd, d[i][(lm >> i) - 1], dd);
                lm -= 1 << i;
            }

            if (rm + (1 << i) <= r) {
                // cout << 'r' << rm << '-' << rm + (1 << i) << endl;
                merge(dd, d[i][rm >> i], dd);
                rm += 1 << i;
            }
        }

        // cout << dd[0] << ' ' << dd[1] << ' ' << dd[2] << ' ' << dd[3] << endl;
        // cout << dd[4] << ' ' << dd[5] << ' ' << dd[6] << ' ' << dd[7] << endl;

        int best = 2000000000;

        best = min(best, max(x[dd[XMAX2]] - x[dd[XMIN1]], y[dd[YMAX1] == dd[XMAX1] ? dd[YMAX2] : dd[YMAX1]] - y[dd[YMIN1] == dd[XMAX1] ? dd[YMIN2] : dd[YMIN1]]));
        best = min(best, max(x[dd[XMAX1]] - x[dd[XMIN2]], y[dd[YMAX1] == dd[XMIN1] ? dd[YMAX2] : dd[YMAX1]] - y[dd[YMIN1] == dd[XMIN1] ? dd[YMIN2] : dd[YMIN1]]));
        best = min(best, max(x[dd[XMAX1] == dd[YMAX1] ? dd[XMAX2] : dd[XMAX1]] - x[dd[XMIN1] == dd[YMAX1] ? dd[XMIN2] : dd[XMIN1]], y[dd[YMAX2]] - y[dd[YMIN1]]));
        best = min(best, max(x[dd[XMAX1] == dd[YMIN1] ? dd[XMAX2] : dd[XMAX1]] - x[dd[XMIN1] == dd[YMIN1] ? dd[XMIN2] : dd[XMIN1]], y[dd[YMAX1]] - y[dd[YMIN2]]));

        printf("%d\n", max(best, 0));
    }

    return 0;
}
