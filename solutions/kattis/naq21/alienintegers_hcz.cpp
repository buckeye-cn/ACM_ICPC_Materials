// https://open.kattis.com/problems/alienintegers

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

    long n;
    cin >> n;

    string s = to_string(n);

    int mask = 0;

    for (int i = 0; i < s.size(); ++i) {
        mask |= 1 << (s[i] - '0');
    }

    if (mask == 1023) {
        cout << "Impossible" << endl;
    } else if (mask == 1022) {
        cout << 0 << endl;
    } else if (n == 0) {
        cout << 1 << endl;
    } else {
        long l = 0;
        long r = 0;

        for (long i = s[0] - '0'; i >= 1; --i) {
            if (mask & (1l << i)) continue;
            l = i;
            break;
        }

        for (long i = 9; i >= 1; --i) {
            if (mask & (1l << i)) continue;
            while (n > l * 10 + i) {
                l = l * 10 + i;
            }
            break;
        }

        for (long i = s[0] - '0'; i <= 9; ++i) {
            if (mask & (1l << i)) continue;
            r = i;
            break;
        }

        if (!r) {
            for (long i = 1; i <= 9; ++i) {
                if (mask & (1l << i)) continue;
                r = i;
                break;
            }
        }

        for (long i = 0; i <= 9; ++i) {
            if (mask & (1l << i)) continue;
            while (n > r) {
                r = r * 10 + i;
            }
            break;
        }

        if (r - n > n - l) {
            cout << l << endl;
        } else if (r - n == n - l) {
            cout << l << ' ' << r << endl;
        } else {
            cout << r << endl;
        }
    }

    return 0;
}
