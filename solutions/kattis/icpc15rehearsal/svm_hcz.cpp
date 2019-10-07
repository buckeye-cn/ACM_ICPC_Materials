// https://open.kattis.com/problems/svm

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

    double w_val[n];
    double w_abs = 0;

    for (int i = 0; i < n; ++i) {
        double w;
        cin >> w;

        w_val[i] = w;
        w_abs += w * w;
    }

    w_abs = sqrt(w_abs);

    double b;
    cin >> b;

    while (true) {
        double wx = b;

        for (int i = 0; i < n; ++i) {
            double x;
            cin >> x;

            if (cin.eof()) {
                return 0;
            }

            wx += w_val[i] * x;
        }

        cout << wx / w_abs << endl;
    }
}
