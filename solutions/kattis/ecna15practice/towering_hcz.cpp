// https://open.kattis.com/problems/towering

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
    cout.precision(15);

    int a[6];
    int h[2];
    cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> h[0] >> h[1];

    for (int c = 0; c < 2; ++c) {
        if (c) cout << ' ';
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int k = 0; k < 6; ++k) {
                    if (
                        i != j && j != k
                        && a[i] > a[j] && a[j] > a[k]
                    ) {
                        if (a[i] + a[j] + a[k] == h[c]) {
                            cout << a[i] << ' ' << a[j] << ' ' << a[k];
                        }
                    }
                }
            }
        }
    }

    return 0;
}
