#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long n[500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        memset(n, 0, sizeof(n));

        int m;
        cin >> m;

        long gsum = 0;

        for (int i = 0; i < m; ++i) {
            int p;
            cin >> p >> n[p];

            gsum += p * n[p];
        }

        for (int i = 2; true; ++i) {
            if (i > 3025 || gsum - i < 2) {
                cout << 0 << endl;
                break;
            }

            long sum = i;
            long mul = gsum - i;

            for (int j = 2; j < 500; ++j) {
                for (int k = 0; k < n[j] && mul % j == 0; ++k) {
                    sum -= j;
                    mul /= j;
                }
            }

            if (sum == 0 && mul == 1) {
                cout << gsum - i << endl;
                break;
            }
        }
    }

    return 0;
}
