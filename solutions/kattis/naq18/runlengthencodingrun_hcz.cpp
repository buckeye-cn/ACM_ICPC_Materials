// https://open.kattis.com/problems/runlengthencodingrun

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

    char c;
    cin >> c;

    string s;
    cin >> s;

    if (c == 'E') {
        char last = 0;
        int count = 0;

        for (char i: s) {
            if (i != last) {
                if (count) {
                    cout << last << count;
                }
                count = 0;
            }

            last = i;
            count += 1;
        }

        if (count) {
            cout << last << count;
        }
    } else {
        char rep = 0;
        int count = 0;

        for (char i: s) {
            if (i >= '0' && i <= '9') {
                count *= 10;
                count += i - '0';
            } else {
                while (count) {
                    cout << rep;
                    count -= 1;
                }
                rep = i;
            }

            while (count) {
                cout << rep;
                count -= 1;
            }
        }
    }

    cout << endl;

    return 0;
}
