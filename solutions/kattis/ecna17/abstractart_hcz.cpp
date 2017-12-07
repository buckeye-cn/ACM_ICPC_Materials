// https://open.kattis.com/problems/abstractart
// might TLE/MLE in some tricky cases

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define sqr(x) ((x) * (x))

const double DELTA = 1e-9;

using namespace std;

int n;
int m[100];

int x[100][21];
int y[100][21];

double s1, s2;

struct point {
    double x;
    double y;
};

using line = point [2];

struct triangle {
    line base;
    double s;
};

struct polygon {
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    vector<triangle> t;
    double s;
};

vector<polygon> polys;

double cross(const point &p, const point &q) {
    return p.x * q.y - q.x * p.y;
}

point line_intersect(const line &p, const line &q) {
    point pp = {p[1].x - p[0].x, p[1].y - p[0].y};
    point qq = {q[1].x - q[0].x, q[1].y - q[0].y};

    double pxqy = pp.x * qq.y;
    double pyqx = pp.y * qq.x;
    double pxqx = pp.x * qq.x;
    double pyqy = pp.y * qq.y;

    return {
        (p[0].y * pxqx - p[0].x * pyqx - q[0].y * pxqx + q[0].x * pxqy) / (pxqy - pyqx),
        (p[1].x * pyqy - p[1].y * pxqy - q[1].x * pyqy + q[1].y * pyqx) / (pyqx - pxqy),
    };
}

void put_triangle(polygon &poly, const point &p, const point &q) {
    double s = cross(p, q);

    if (s > DELTA || s < -DELTA) {
        poly.t.push_back({{p, q}, s});
        poly.s += s;
    }
}

void put_intersect_triangle(polygon &poly, triangle &p, triangle &q) {
    bool ab = p.s > DELTA;
    bool cd = q.s > DELTA;

    point &a = p.base[!ab];
    point &b = p.base[ab];
    point &c = q.base[!cd];
    point &d = q.base[cd];

    bool cb = cross(c, b) > DELTA;
    if (!cb) return;
    bool ad = cross(a, d) > DELTA;
    if (!ad) return;

    bool ac = cross(a, c) > DELTA;
    bool bd = cross(b, d) > DELTA;

    point &l = ac ? c : a;
    point &r = bd ? b : d;
    point l1 = line_intersect({{}, l}, ac ? p.base : q.base);
    if (sqr(l.x) + sqr(l.y) < sqr(l1.x) + sqr(l1.y)) l1 = l;
    point r1 = line_intersect({{}, r}, bd ? q.base : p.base);
    if (sqr(r.x) + sqr(r.y) < sqr(r1.x) + sqr(r1.y)) r1 = r;

    point x = line_intersect(p.base, q.base);

    bool lx = cross(l, x) > DELTA;
    bool xr = cross(x, r) > DELTA;

    if (lx && xr) {
        put_triangle(
            poly,
            x,
            ab == cd ? l1 : r1
        );
        put_triangle(
            poly,
            ab == cd ? r1 : l1,
            x
        );
    } else {
        put_triangle(
            poly,
            ab == cd ? r1 : l1,
            ab == cd ? l1 : r1
        );
    }
}

void put_intersect_polygon(polygon &p, polygon &q) {
    int x_min = max(p.x_min, q.x_min);
    int y_min = max(p.y_min, q.y_min);
    int x_max = min(p.x_max, q.x_max);
    int y_max = min(p.y_max, q.y_max);
    if (x_min >= x_max || y_min >= y_max) return;

    polygon poly = {
        x_min, y_min, x_max, y_max, {}
    };

    for (int i = 0; i < p.t.size(); ++i) {
        for (int j = 0; j < q.t.size(); ++j) {
            put_intersect_triangle(poly, p.t[i], q.t[j]);

            // TODO: merge polygons when possible
            // if (abs(p.t[i].s) < DELTA) {
            //     p.t[i] = p.t.back();
            //     p.t.pop_back();
            // }
            // if (abs(q.t[j].s) < DELTA) {
            //     q.t[j] = q.t.back();
            //     q.t.pop_back();
            // }
        }
    }

    if (poly.t.size()) {
        polys.push_back(std::move(poly));
    }
}

void put_polygon(polygon &&poly) {
    int len = polys.size();
    for (int i = 0; i < len; ++i) {
        put_intersect_polygon(poly, polys[i]);

        // already covered
        if (polys.back().s == -poly.s) {
            polys.resize(len);
            return;
        }
    }

    if (poly.t.size()) {
        polys.push_back(std::move(poly));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        // input

        cin >> m[i];

        for (int j = 0; j < m[i]; ++j) {
            cin >> x[i][j] >> y[i][j];
        }

        // boundary

        x[i][m[i]] = x[i][0];
        y[i][m[i]] = y[i][0];

        int x_min = x[i][0];
        int x_max = x[i][0];
        int y_min = y[i][0];
        int y_max = y[i][0];

        for (int j = 1; j < m[i]; ++j) {
            x_min = min(x_min, x[i][j]);
            x_max = max(x_max, x[i][j]);
            y_min = min(y_min, y[i][j]);
            y_max = max(y_max, y[i][j]);
        }

        // size

        int s = 0;

        for (int j = 0; j < m[i]; ++j) {
            s += x[i][j] * y[i][j + 1] - x[i][j + 1] * y[i][j];
        }

        s1 += abs(s);

        // polygon

        polygon poly = {
            x_min, y_min, x_max, y_max, {}
        };

        for (int j = 0; j < m[i]; ++j) {
            put_triangle(
                poly,
                {double(x[i][j + (s < 0)]), double(y[i][j + (s < 0)])},
                {double(x[i][j + (s >= 0)]), double(y[i][j + (s >= 0)])}
            );
        }

        put_polygon(std::move(poly));
    }

    for (polygon &poly: polys) {
        s2 += poly.s;
    }

    cout << 0.5 * s1 << ' ' << 0.5 * s2 << endl;

    return 0;
}
