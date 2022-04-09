#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int values[200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        int n;
        cin >> n;

        long total = 0;

        for (int i = 0; i < n; ++i) {
            values[i] = i < 30 ? 1 << i : 128 + i;
            total += values[i];

            if (i) {
                cout << ' ';
            }
            cout << values[i];
        }
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cin >> values[n + i];

            total += values[n + i];
        }

        total /= 2;

        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n - 1; ++j) {
                if (values[j] < values[j + 1]) {
                    swap(values[j], values[j + 1]);
                }
            }
        }

        for (int i = 0; i < 2 * n; ++i) {
            if (total == values[i] || i == 2 * n - 1) {
                cout << values[i] << endl;
                break;
            }

            if (total > values[i]) {
                total -= values[i];

                cout << values[i] << ' ';
            }
        }
    }

    return 0;
}
