#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ':' << endl;

        double a;
        cin >> a;

        double tt = asin(a / sqrt(3)) - asin(1 / sqrt(3));
        double unit = sqrt(2) / 4;

        cout << unit << ' ' << unit * sin(tt) << ' ' << unit * cos(tt) << endl;
        cout << -unit << ' ' << unit * sin(tt) << ' ' << unit * cos(tt) << endl;
        cout << 0 << ' ' << 0.5 * cos(tt) << ' ' << -0.5 * sin(tt) << endl;
    }

    return 0;
}
