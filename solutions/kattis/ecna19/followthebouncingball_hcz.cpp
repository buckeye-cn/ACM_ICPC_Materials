// https://open.kattis.com/problems/followthebouncingball

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

#define sqr(x) ((x) * (x))
#define sign(x) (((x) > 1e-10) - ((x) < -1e-10))

using namespace std;

void intersect(
    double &x, double &y,
    double px1, double py1, double px2, double py2,
    double qx1, double qy1, double qx2, double qy2
) {
    double px = px2 - px1;
    double py = py2 - py1;
    double qx = qx2 - qx1;
    double qy = qy2 - qy1;

    double pxqy = px * qy;
    double pyqx = py * qx;
    double pxqx = px * qx;
    double pyqy = py * qy;

    x = (py1 * pxqx - px1 * pyqx - qy1 * pxqx + qx1 * pxqy) / (pxqy - pyqx);
    y = (px2 * pyqy - py2 * pxqy - qx2 * pyqy + qy2 * pyqx) / (pyqx - pxqy);
}

void reflect(
    double &x, double &y,
    double px, double py,
    double qx, double qy
) {
    double pxqy = px * qy;
    double pyqx = py * qx;

    x = px - 2 * (pxqy - pyqx) * qy / (sqr(qx) + sqr(qy));
    y = py - 2 * (pyqx - pxqy) * qx / (sqr(qx) + sqr(qy));
}

int n;
double nx[500];
double ny[500];
double vx[500];
double vy[500];

int m;
int mp[21];
double mx[21][11];
double my[21][11];
int mq[21];

int cj[500];
int ck[500];
double cx[500];
double cy[500];

set<pair<double, int>> q;

void update(double t, int i, int from_j, int from_k) {
    double best_t = INFINITY;

    for (int j = 0; j <= m; ++j) {
        if (!mq[j]) continue;

        for (int k = 0; k < mp[j]; ++k) {
            if (j == from_j && k == from_k) continue;

            double x, y;

            intersect(
                x, y,
                nx[i], ny[i], nx[i] + vx[i], ny[i] + vy[i],
                mx[j][k], my[j][k], mx[j][k + 1], my[j][k + 1]
            );

            if (
                sign(x - mx[j][k]) == sign(mx[j][k + 1] - x)
                && sign(y - my[j][k]) == sign(my[j][k + 1] - y)
                && sign(x - nx[i]) == sign(vx[i])
                && sign(y - ny[i]) == sign(vy[i])
            ) {
                double curr_t;

                if (vx[i] != 0) {
                    curr_t = t + (x - nx[i]) / vx[i];
                } else {
                    curr_t = t + (y - ny[i]) / vy[i];
                }

                if (best_t > curr_t) {
                    best_t = curr_t;
                    cj[i] = j;
                    ck[i] = k;
                    cx[i] = x;
                    cy[i] = y;
                }
            }
        }
    }

    if (best_t < INFINITY) {
        q.insert({best_t, i});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double w, h;
    double l, r, s;
    cin >> w >> h >> n >> m >> l >> r >> s;

    double rs_norm = sqrt(sqr(r) + sqr(s));
    r /= rs_norm;
    s /= rs_norm;

    for (int i = 0; i < n; ++i) {
        nx[i] = l - r * i;
        ny[i] = -s * i;
        vx[i] = r;
        vy[i] = s;
    }

    for (int i = 0; i < m; ++i) {
        cin >> mp[i];

        for (int j = 0; j < mp[i]; ++j) {
            cin >> mx[i][j] >> my[i][j];
        }

        mx[i][mp[i]] = mx[i][0];
        my[i][mp[i]] = my[i][0];

        cin >> mq[i];
    }

    mp[m] = 3;
    mx[m][0] = 0;
    my[m][0] = 0;
    mx[m][1] = 0;
    my[m][1] = h;
    mx[m][2] = w;
    my[m][2] = h;
    mx[m][3] = w;
    my[m][3] = 0;
    mq[m] = 1e9;

    for (int i = 0; i < n; ++i) {
        update(0, i, -1, -1);
    }

    while (!q.empty()) {
        double t = q.begin()->first;

        int n_same = 0;
        int ii[500];

        while (!q.empty() && !sign(q.begin()->first - t)) {
            ii[n_same++] = q.begin()->second;
            q.erase(q.begin());
        }

        for (int l = 0; l < n_same; ++l) {
            int i = ii[l];
            int j = cj[i];

            if (mq[j] > 0) {
                mq[j] -= 1;
            }
        }

        for (int l = 0; l < n_same; ++l) {
            int i = ii[l];
            int j = cj[i];
            int k = ck[i];

            nx[i] = cx[i];
            ny[i] = cy[i];

            if (mq[j] > 0) {
                reflect(
                    vx[i], vy[i],
                    vx[i], vy[i],
                    mx[j][k + 1] - mx[j][k], my[j][k + 1] - my[j][k]
                );
            }

            // cerr << t << '\t' << i << '\t';
            // cerr << j << '(' << (j == m ? -1 : mq[j]) << ')' << '\t';
            // cerr << nx[i] << ':' << ny[i] << '\t' << vx[i] << ':' << vy[i] << '\t';
            // cerr << (mq[j] > 0 ? 'b' : '-') << endl;

            update(t, i, j, k);
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << mq[i];

        if (i == m - 1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }

    return 0;
}
