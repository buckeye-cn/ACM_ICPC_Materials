// https://open.kattis.com/problems/engineeringenglish

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool bf[2][1048576];

int main() {
    string s;

    while (cin >> s) {
        long h0 = 0;
        long h1 = 0;

        for (char c: s) {
            h0 = (h0 * 1234567 + c % 32 * 7654321) % 1048576;
            h1 = (h1 * 7876543 + c % 32 * 3456787) % 1048576;
        }

        if (bf[0][h0] && bf[1][h1]) {
            cout << ". ";
        } else {
            bf[0][h0] = true;
            bf[1][h1] = true;
            cout << s << ' ';
        }
    }

    return 0;
}
