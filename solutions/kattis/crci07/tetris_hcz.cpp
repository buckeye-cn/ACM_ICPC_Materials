// https://open.kattis.com/problems/tetris

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int c, p;
int h[100];

int test(string s) {
    int tot = 0;

    for (int i = 0; i <= c - s.size(); ++i) {
        bool ok = true;

        for (int j = 1; j < s.size(); ++j) {
            ok &= h[i + j] - h[i] == s[j] - s[0];
        }

        tot += ok;
    }

    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> c >> p;

    for (int i = 0; i < c; ++i) {
        cin >> h[i];
    }

    switch (p) {
        case 1:
            cout << test("0") + test("0000") << endl;
            break;
        case 2:
            cout << test("00") << endl;
            break;
        case 3:
            cout << test("001") + test("10") << endl;
            break;
        case 4:
            cout << test("100") + test("01") << endl;
            break;
        case 5:
            cout << test("000") + test("101") + test("01") + test("10") << endl;
            break;
        case 6:
            cout << test("000") + test("011") + test("20") + test("00") << endl;
            break;
        case 7:
            cout << test("000") + test("110") + test("00") + test("02") << endl;
            break;
    }

    return 0;
}
