// https://open.kattis.com/problems/mountainbiking

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

    int n;
    double g;
    cin >> n >> g;

    double v2[n];

    for (int i = 0; i < n; ++i) {
        double d, a;
        cin >> d >> a;

        v2[i] = d * g * cos(a * PI / 180) * 2;
    }

    for (int i = n - 1; i >= 0; --i) {
        v2[i] += v2[i + 1];
    }

    for (int i = 0; i < n; ++i) {
        cout << sqrt(v2[i]) << endl;
    }

    return 0;
}
