// https://open.kattis.com/problems/amsterdamdistance

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    double r;
    cin >> r;

    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;

    double best = INFINITY;

    for (int i = 0; i <= min(ay, by); ++i) {
        double d1 = r * (ay - i) / n;
        double d2 = PI * r * abs(ax - bx) * i / m / n;
        double d3 = r * (by - i) / n;

        best = min(best, d1 + d2 + d3);
    }

    cout << best << endl;

    return 0;
}
