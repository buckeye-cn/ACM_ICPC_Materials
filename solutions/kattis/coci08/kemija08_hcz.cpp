// https://open.kattis.com/problems/kemija08

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

    bool first = true;
    string s;

    while (cin >> s) {
        if (first) {
            first = false;
        } else {
            cout << ' ';
        }

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
                i += 2;
            }

            cout << s[i];
        }
    }

    cout << endl;

    return 0;
}
