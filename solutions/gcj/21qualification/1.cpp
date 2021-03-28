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

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int n;
        cin >> n;

        int l[n];
        for (int i = 0; i < n; ++i) {
            cin >> l[i];
        }

        int tot = 0;

        for (int i = 0; i < n - 1; ++i) {
            int j_min = i;

            for (int j = i; j < n; ++j) {
                if (l[j_min] > l[j]) {
                    j_min = j;
                }
            }

            tot += j_min - i + 1;

            for (int j = 0; i + j < j_min - j; ++j) {
                int t = l[i + j];

                l[i + j] = l[j_min - j];
                l[j_min - j] = t;
            }
        }

        cout << tot << endl;
    }

    return 0;
}
