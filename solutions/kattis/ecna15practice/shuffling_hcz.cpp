// https://open.kattis.com/problems/shuffling

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
    string io;
    cin >> n >> io;

    int list[n];
    for (int i = 0; i < n; ++i) {
        list[i] = i;
    }

    for (int count = 1; true; ++count) {
        int list2[n];

        if (io == "out") {
            for (int i = 0; i < n; ++i) {
                int i2 = i - (n + 1) / 2;
                if (i2 < 0) {
                    list2[2 * i] = list[i];
                } else {
                    list2[2 * i2 + 1] = list[i];
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                int i2 = i - n / 2;
                if (i2 < 0) {
                    list2[2 * i + 1] = list[i];
                } else {
                    list2[2 * i2] = list[i];
                }
            }
        }

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            list[i] = list2[i];
            ok &= list[i] == i;
        }

        if (ok) {
            cout << count << endl;

            return 0;
        }
    }
}
