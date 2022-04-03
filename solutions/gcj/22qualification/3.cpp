#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int c[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        memset(c, 0, sizeof(c));

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int s;
            cin >> s;

            c[s] += 1;
        }

        for (int i = 1000000; i >= 1; --i) {
            c[i - 1] += c[i];
        }

        for (int i = 1; i <= 1000000; ++i) {
            c[i] = min(c[i - 1], c[i] + i - 1);
        }

        cout << c[1000000] << endl;
    }

    return 0;
}
