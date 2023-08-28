// https://open.kattis.com/problems/peapattern

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

    string s, t;
    cin >> s >> t;

    for (int i = 1; i <= 100; ++i) {
        if (s == t) {
            cout << i << endl;

            return 0;
        }

        int nn[10];
        memset(nn, 0, sizeof(nn));

        for (char c: s) {
            nn[c - '0'] += 1;
        }

        string ss;

        for (char c = '0'; c <= '9'; ++c) {
            if (nn[c - '0']) {
                ss += to_string(nn[c - '0']);
                ss += c;
            }
        }

        s = ss;
    }

    cout << "Does not appear" << endl;

    return 0;
}
