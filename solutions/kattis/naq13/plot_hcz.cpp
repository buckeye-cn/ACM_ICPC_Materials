// https://open.kattis.com/problems/plot

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

    int coeff[n + 1];

    for (int i = n; i >= 0; --i) {
        cin >> coeff[i];
    }

    int c[n + 1];

    for (int i = 0; i <= n; ++i) {
        c[i] = 0;

        int pow_i = 1;
        for (int j = 0; j <= n; ++j) {
            c[i] += pow_i * coeff[j];
            pow_i *= i;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = n; j > i; --j) {
            c[j] -= c[j - 1];
        }
    }

    for (int i = 0; i <= n; ++i) {
        if (i) {
            cout << ' ';
        }

        cout << c[i];
    }

    cout << endl;

    return 0;
}
