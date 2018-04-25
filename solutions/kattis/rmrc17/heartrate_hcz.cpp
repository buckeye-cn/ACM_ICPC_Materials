// https://open.kattis.com/problems/heartrate

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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int b;
        double p;
        cin >> b >> p;

        printf(
            "%.4f %.4f %.4f\n",
            (b - 1) * 60. / p,
            b * 60. / p,
            (b + 1) * 60 / p
        );
    }

    return 0;
}
