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
        cout << "Case #" << n_case << ':' << endl;

        int r, c;
        cin >> r >> c;

        for (int i = 0; i <= r; ++i) {
            if (i) {
                for (int j = 0; j <= c; ++j) {
                    if (j) {
                        cout << '.';
                    }
                    if (i > 1 || j) {
                        cout << '|';
                    } else {
                        cout << '.';
                    }
                }
                cout << endl;
            }

            for (int j = 0; j <= c; ++j) {
                if (j) {
                    if (i || j > 1) {
                        cout << '-';
                    } else {
                        cout << '.';
                    }
                }
                if (i || j) {
                    cout << '+';
                } else {
                    cout << '.';
                }
            }
            cout << endl;
        }
    }

    return 0;
}
