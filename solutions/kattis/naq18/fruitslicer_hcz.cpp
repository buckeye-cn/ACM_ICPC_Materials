// https://open.kattis.com/problems/fruitslicer

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const double PI = acos(-1);

using namespace std;

int n;
double x[100];
double y[100];

pair<int, double> test(double rot) {
    int result = 0;

    pair<double, bool> range[2 * n];

    for (int i = 0; i < n; ++i) {
        range[2 * i].first = x[i] * sin(rot) - y[i] * cos(rot) - 1.000001;
        range[2 * i].second = false;
        range[2 * i + 1].first = x[i] * sin(rot) - y[i] * cos(rot) + 1.000001;
        range[2 * i + 1].second = true;
    }

    sort(range, range + 2 * n);

    int current = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (!range[i].second) {
            current += 1;
        } else {
            current -= 1;
        }

        result = max(result, current);
    }

    return {result, rot};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    pair<int, double> best {0, 0};

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            best = max(best, test(atan2(y[j] - y[i], x[j] - x[i])));
        }
    }

    for (double rot = 0; rot < PI; rot += 1e-2) {
        best = max(best, test(rot));
    }

    for (double delta = 1e-2; delta >= 1e-8; delta *= 0.5) {
        best = max(best, test(best.second + delta));
        best = max(best, test(best.second - delta));
    }

    cout << best.first << endl;

    return 0;
}
