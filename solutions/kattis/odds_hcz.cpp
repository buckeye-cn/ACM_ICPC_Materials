// https://open.kattis.com/problems/odds

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int chance[7][7][7][7];

int gcd(int a, int b) {
    if (a > b) {
        if (a % b == 0) {
            return b;
        } else {
            return gcd(a % b, b);
        }
    } else {
        if (b % a == 0) {
            return a;
        } else {
            return gcd(b % a, a);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int s1 = 1; s1 <= 6; ++s1) {
        for (int s0 = 1; s0 <= 6; ++s0) {
            for (int r1 = 1; r1 <= 6; ++r1) {
                for (int r0 = 1; r0 <= 6; ++r0) {
                    int s = s0 > s1 ? s0 * 10 + s1 : s1 * 10 + s0;
                    if (s0 == s1) s += 100;
                    if (s == 21) s += 200;

                    int r = r0 > r1 ? r0 * 10 + r1 : r1 * 10 + r0;
                    if (r0 == r1) r += 100;
                    if (r == 21) r += 200;

                    int v = s > r ? 1 : 0;
                    chance[s0][s1][r0][r1] += v;
                    chance[s0][0][r0][r1] += v;
                    chance[0][s1][r0][r1] += v;
                    chance[0][0][r0][r1] += v;
                    chance[s0][s1][r0][0] += v;
                    chance[s0][0][r0][0] += v;
                    chance[0][s1][r0][0] += v;
                    chance[0][0][r0][0] += v;
                    chance[s0][s1][0][r1] += v;
                    chance[s0][0][0][r1] += v;
                    chance[0][s1][0][r1] += v;
                    chance[0][0][0][r1] += v;
                    chance[s0][s1][0][0] += v;
                    chance[s0][0][0][0] += v;
                    chance[0][s1][0][0] += v;
                    chance[0][0][0][0] += v;
                }
            }
        }
    }

    while (true) {
        char a, b, c, d;

        cin >> a >> b >> c >> d;

        if (a == '0') {
            // b, c, d are '0' too
            return 0;
        }

        int s0, s1, r0, r1;

        s0 = a == '*' ? 0 : a - '0';
        s1 = b == '*' ? 0 : b - '0';
        r0 = c == '*' ? 0 : c - '0';
        r1 = d == '*' ? 0 : d - '0';

        int ch = chance[s0][s1][r0][r1];
        int base = (s0 ? 1 : 6) * (s1 ? 1 : 6) * (r0 ? 1 : 6) * (r1 ? 1 : 6);

        if (ch == 0) {
            cout << '0' << endl;
        } else if (ch == base) {
            cout << '1' << endl;
        } else {
            int g = gcd(ch, base);
            cout << (ch / g) << '/' << (base / g) << endl;
        }
    }
}
