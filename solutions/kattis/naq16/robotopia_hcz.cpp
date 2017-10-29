// https://open.kattis.com/problems/robotopia

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
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long l1, a1, l2, a2, lt, at;

        cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;

        bool found = false;
        long first_n1, first_n2;
        for (long n1 = 1; n1 <= 10000; ++n1) {
            long n2 = (lt - n1 * l1) / l2;

            if (n2 <= 0) break;
            if (n1 * l1 + n2 * l2 == lt && n1 * a1 + n2 * a2 == at) {
                if (found) {
                    found = false;
                    break;
                } else {
                    found = true;
                    first_n1 = n1;
                    first_n2 = n2;
                }
            }
        }

        if (found) {
            cout << first_n1 << ' ' << first_n2 << endl;
        } else {
            cout << '?' << endl;
        }
    }

    return 0;
}
