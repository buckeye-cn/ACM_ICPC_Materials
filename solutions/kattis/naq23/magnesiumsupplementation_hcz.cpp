// https://open.kattis.com/problems/magnesiumsupplementation

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int nn;
long vv[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n, k, p;
    cin >> n >> k >> p;

    for (long i = 1; i <= k && i * i < n; ++i) {
        if (n % i == 0 && n / i <= p) {
            vv[nn++] = i;
        }
    }

    for (long i = sqrt(n); i; --i) {
        if (n % i == 0 && n / i <= k) {
            vv[nn++] = n / i;
        }
    }

    cout << nn << endl;

    for (int i = 0; i < nn; ++i) {
        cout << vv[i] << endl;
    }

    return 0;
}
