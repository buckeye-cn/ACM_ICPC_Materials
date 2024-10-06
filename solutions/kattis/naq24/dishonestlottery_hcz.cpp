// https://open.kattis.com/problems/dishonestlottery

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int xslot[51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < 50 * n; ++i) {
        int x;
        cin >> x;

        xslot[x] += 1;
    }

    bool first = true;

    for (int x = 1; x <= 50; ++x) {
        if (xslot[x] > 2 * n) {
            if (first) {
                first = false;
            } else {
                cout << ' ';
            }

            cout << x;
        }
    }

    if (first) {
        cout << -1;
    }

    cout << endl;

    return 0;
}
