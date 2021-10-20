// https://open.kattis.com/problems/friday

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

    for (int i = 0; i < t; ++i) {
        int d, m;
        cin >> d >> m;

        int dx = 0;
        int tot = 0;

        for (int i = 0; i < m; ++i) {
            int dd;
            cin >> dd;

            if (dd >= 13) {
                dx += (tot + 13) % 7 == 6;
            }

            tot += dd;
        }

        cout << dx << endl;
    }

    return 0;
}
