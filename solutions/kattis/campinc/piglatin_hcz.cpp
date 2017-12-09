// https://open.kattis.com/problems/piglatin

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

    while (true) {
        string s;
        cin >> s;

        if (!s.size()) break;

        char c = cin.get();

        int pos;
        for (pos = 0; pos < s.size(); ++pos) {
            bool vowel = false;

            switch (s[pos]) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                case 'y':
                    vowel = true;
                    break;
            }

            if (vowel) break;

        }

        if (pos) {
            cout << s.substr(pos) << s.substr(0, pos) << "ay" << c;
        } else {
            cout << s << "yay" << c;
        }
    }

    return 0;
}
