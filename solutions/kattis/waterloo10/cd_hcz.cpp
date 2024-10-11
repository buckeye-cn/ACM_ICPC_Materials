// https://open.kattis.com/problems/cd

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

    for (int nn = 0; true; ++nn) {
        int n, m;
        cin >> n >> m;

        if (!n && !m) return 0;

        int tot = 0;

        int a[n + 1];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        a[n] = 1 << 30;

        for (int i = 0, j = 0; j < m; ++j) {
            int b;
            cin >> b;

            while (b > a[i]) {
                ++i;
            }
            if (b == a[i]) {
                ++tot;
            }
        }

        cout << tot << endl;
    }
}
