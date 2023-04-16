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

        long n;
        cin >> n;

        for (int i = 1; true; ++i) {
            if (n <= 26 * i) {
                cout << char('A' + ((n - 1) / i)) << endl;
                break;
            } else {
                n -= 26 * i;
            }
        }
    }

    return 0;
}
