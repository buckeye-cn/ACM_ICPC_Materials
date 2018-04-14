// not AC

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

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ":" << endl;

        double a;
        cin >> a;

        // if (a <= sqrt(2)) {
        //     double t1 = (a + sqrt(2 - a * a)) / 4;
        //     double t2 = sqrt(sqr(0.5) - sqr(t1));

        //     cout << t1 << ' ' << t2 << ' ' << 0 << endl;
        //     cout << -t2 << ' ' << t1 << ' ' << 0 << endl;
        //     cout << 0 << ' ' << 0 << ' ' << 0.5 << endl;
        // }

        double tt = asin(a / sqrt(3)) - asin(1 / sqrt(3));
        double unit = sqrt(2) / 4;

        cout << unit * sin(tt) << ' ' << unit * cos(tt) << ' ' << unit << endl;
        cout << -unit * sin(tt) << ' ' << unit * cos(tt) << ' ' << unit << endl;
        cout << unit * cos(tt) << ' ' << unit * sin(tt) << ' ' << 0 << endl;
    }

    return 0;
}
