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
        int a, b, n;
        cin >> a >> b >> n;

        for (int i = 29; i >= 0; --i) {
            if (a + (1 << i) > b) continue;

            cout << (a + (1 << i)) << endl;

            string s;
            cin >> s;

            if (s == "TOO_SMALL") {
                a += 1 << i;
            } else if (s == "TOO_BIG") {
                // nothing
            } else {
                break;
            }
        }
    }

    return 0;
}
