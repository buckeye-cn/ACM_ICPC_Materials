// https://open.kattis.com/problems/progressivescramble

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        char cmd;
        cin >> cmd;

        cin.get();
        int last = 0;
        while (true) {
            char c = cin.get();
            if (c == '\n') break;

            int k = 0;
            if (c >= 'a' && c <= 'z') {
                k = c - 'a' + 1;
            }

            int result;
            if (cmd == 'e') {
                last = last + k;
                last %= 27;
                result = last;
            } else {
                last = k - last + 27;
                last %= 27;
                result = last;
                last = k;
            }
            if (result == 0) {
                cout << ' ';
            } else {
                cout << char('a' + result - 1);
            }
        }

        cout << endl;
    }

    return 0;
}
