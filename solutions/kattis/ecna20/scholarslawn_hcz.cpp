// https://open.kattis.com/problems/scholarslawn

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

template <long N>
struct SPFA {
    struct Edge {
        long to, len;
    };

    vector<Edge> edges;
    vector<long> outs[N];

    void add(long from, long to, long len) {
        edges.push_back({to, len});
        outs[from].push_back(edges.size() - 1);
    }

    long dist[N];
    long route[N];
    long visiting[N];
    bool active[N];

    long solve(long from, long to) {
        memset(active, 0, sizeof(active));

        for (int i = 0; i < N; ++i) {
            dist[i] = 1l << 60;
        }

        long head = 0;
        long tail = 0;

        dist[from] = 0;
        visiting[(tail++) % N] = from;
        active[from] = true;

        while (head < tail) {
            long i = visiting[(head++) % N];
            active[i] = false;

            for (long j = 0; j < outs[i].size(); ++j) {
                Edge &e = edges[outs[i][j]];

                if (dist[e.to] > dist[i] + e.len) {
                    dist[e.to] = dist[i] + e.len;
                    route[e.to] = i;

                    if (!active[e.to]) {
                        visiting[(tail++) % N] = e.to;
                        active[e.to] = true;
                    }
                }
            }
        }

        return dist[to];
    }
};

SPFA<126000> spfa;

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

long pointhash(double x, double y) {
    return round(1234567 * x + 7654321 * y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    double x1[501];
    double y1[501];
    double x2[501];
    double y2[501];
    double xs, ys, vs;
    double vf;

    unordered_map<long, int> m;
    set<pair<double, double>> px[501];

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    cin >> xs >> ys >> vs;
    cin >> x1[0] >> y1[0] >> x2[0] >> y2[0] >> vf;

    m.insert({pointhash(xs, ys), 0});

    for (int i = 0; i <= n; ++i) {
        if (
            abs((xs - x1[i]) * (y2[i] - y1[i]) - (x2[i] - x1[i]) * (ys - y1[i])) < 1e-9
            && xs >= min(x1[i], x2[i])
            && xs <= max(x1[i], x2[i])
            && ys >= min(y1[i], y2[i])
            && ys <= max(y1[i], y2[i])
        ) {
            px[i].insert({xs, ys});
        }

        for (int j = i + 1; j <= n; ++j) {
            double x, y;

            intersect(x, y, x1[i], y1[i], x2[i], y2[i], x1[j], y1[j], x2[j], y2[j]);

            if (
                x >= max(min(x1[i], x2[i]), min(x1[j], x2[j]))
                && x <= min(max(x1[i], x2[i]), max(x1[j], x2[j]))
                && y >= max(min(y1[i], y2[i]), min(y1[j], y2[j]))
                && y <= min(max(y1[i], y2[i]), max(y1[j], y2[j]))
            ) {
                m.insert({pointhash(x, y), m.size()});
                px[i].insert({x, y});
                px[j].insert({x, y});
            }
        }
    }

    for (pair<double, double> p: px[0]) {
        int k = m[pointhash(p.first, p.second)];

        spfa.add(k, 125999, 0);
    }

    for (int i = 1; i <= n; ++i) {
        pair<double, double> prev;
        int prev_k = -1;

        for (pair<double, double> p: px[i]) {
            int k = m[pointhash(p.first, p.second)];

            if (prev_k >= 0) {
                double dist = sqrt(sqr(p.first - prev.first) + sqr(p.second - prev.second));

                spfa.add(prev_k, k, dist * 1e9);
                spfa.add(k, prev_k, dist * 1e9);
            }

            prev = p;
            prev_k = k;
        }
    }

    spfa.solve(0, 125999);

    double best = INFINITY;

    for (pair<double, double> p: px[0]) {
        int k = m[pointhash(p.first, p.second)];
        double dist = sqrt(sqr(p.first - x1[0]) + sqr(p.second - y1[0]));

        if (spfa.dist[k] * 1e-9 / vs <= dist / vf) {
            best = min(best, dist / vf);
        }
    }

    if (best < INFINITY) {
        cout << best << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
