// https://open.kattis.com/problems/primedrive

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool notprime[10000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    notprime[0] = true;
    notprime[1] = true;

    for (int i = 2; i < 5000; ++i) {
        if (notprime[i]) continue;
        for (int j = 2; i * j < 10000; ++j) {
            notprime[i * j] = true;
        }
    }

    while (true) {
        string s;
        int k;
        cin >> s >> k;

        if (s == "END" && !k) {
            return 0;
        }

        k += 10000 * (26 * (26 * (s[0] - 'A') + (s[1] - 'A')) + (s[2] - 'A'));

        while (notprime[k % 10000]) {
            ++k;
        }

        cout << char(k / 10000 / 26 / 26 + 'A')
             << char(k / 10000 / 26 % 26 + 'A')
             << char(k / 10000 % 26 + 'A') << ' ';

        cout.width(4);
        cout.fill('0');
        cout << k % 10000 << endl;
    }
}
