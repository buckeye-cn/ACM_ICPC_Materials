// https://open.kattis.com/problems/largedifferences

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int h[500000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    sort(h, h + n);

    int m1 = 1e9;
    int m2 = 1e9;
    int m2b = 1e9;

    for (int i = 0; i < (n - 1) / 2; ++i) {
        m1 = min(m1, h[i + (n + 1) / 2] - h[i + 1]);
    }

    for (int i = 0; i < (n + 1) / 2; ++i) {
        m2 = min(m2, h[i + n / 2] - h[i]);

        if ((n & 1) && m2b > m2) {
            swap(m2b, m2);
        }
    }

    cout << max(m1, m2) << endl;

    return 0;
}
