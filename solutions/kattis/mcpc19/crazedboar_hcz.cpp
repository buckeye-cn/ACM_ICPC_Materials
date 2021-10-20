// https://open.kattis.com/problems/crazedboar

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

const double PI = acos(-1);
const int STEP = 3600000;

using namespace std;

int n;
double x[10000];
double y[10000];
double r[10000];
double b, d;

char m[STEP];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> r[i];
    }

    cin >> b >> d;

    for (int i = 0; i < n; ++i) {
        r[i] += b;

        double l2 = sqr(x[i]) + sqr(y[i]);
        double l = sqrt(l2);

        double c = atan2(x[i], y[i]);
        double dc;

        if (l2 - sqr(r[i]) <= sqr(d)) {
            dc = asin(r[i] / l);
        } else if (l2 <= sqr(d + r[i])) {
            dc = acos((l2 + sqr(d) - sqr(r[i])) / 2 / l / d);
        } else {
            continue;
        }

        int i1 = (int((c - dc) / PI * STEP / 2) + STEP) % STEP;
        int i2 = (int((c + dc) / PI * STEP / 2) + STEP) % STEP;

        m[i1] += 1;
        m[i2] -= 1;
        m[0] += i1 > i2;
    }

    int cum = 0;
    int total = 0;

    for (int i = 0; i < STEP; i += 4) {
        cum += m[i];
        total += !cum;
    }

    cout << double(total) / STEP << endl;

    return 0;
}
