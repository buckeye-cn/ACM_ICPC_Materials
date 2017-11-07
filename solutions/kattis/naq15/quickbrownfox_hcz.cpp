// https://open.kattis.com/problems/quickbrownfox

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
    char lf;
    cin >> n >> lf;

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);

        int mask = 0;

        for (char c: s) {
            if (c >= 'A' && c <= 'Z') {
                mask |= 1 << (c - 'A');
            } else if (c >= 'a' && c <= 'z') {
                mask |= 1 << (c - 'a');
            }
        }

        if (mask == (1 << 26) - 1) {
            cout << "pangram" << endl;
        } else {
            cout << "missing ";
            for (char c = 'a'; c <= 'z'; ++c) {
                if ((mask & (1 << (c - 'a'))) == 0) {
                    cout << c;
                }
            }
            cout << endl;
        }
    }

    return 0;
}
