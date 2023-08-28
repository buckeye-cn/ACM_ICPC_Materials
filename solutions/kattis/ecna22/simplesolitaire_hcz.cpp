// https://open.kattis.com/problems/simplesolitaire

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

string s[52];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n = 0;

    for (int i = 0; i < 52; ++i) {
        cin >> s[n];
        n += 1;

        bool ok = true;

        while (ok) {
            ok = false;

            for (int j = n - 4; j >= 0; --j) {
                if (s[j][0] == s[j + 3][0]) {
                    for (int k = j; k < n - 4; ++k) {
                        s[k] = s[k + 4];
                    }

                    n -= 4;
                    ok = true;
                    break;
                }
            }

            if (ok) continue;

            for (int j = n - 4; j >= 0; --j) {
                if (s[j][1] == s[j + 3][1]) {
                    s[j] = s[j + 1];
                    s[j + 1] = s[j + 2];

                    for (int k = j; k < n - 4; ++k) {
                        s[k + 2] = s[k + 4];
                    }

                    n -= 2;
                    ok = true;
                    break;
                }
            }
        }
    }

    cout << n;
    for (int i = 0; i < n; ++i) {
        cout << ' ' << s[i];
    }
    cout << endl;

    return 0;
}
