// https://open.kattis.com/problems/neighborhoodwatch

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

    long n, k;
    cin >> n >> k;

    long total = n * (n + 1);
    long last = 0;

    if (n != k) {
        for (long i = 0; i < k; ++i) {
            long h;
            cin >> h;

            total -= (h - last) * (h - last - 1);
            last = h;
        }

        total -= (n - last + 1) * (n - last);
    }

    cout << total / 2 << endl;

    return 0;
}
