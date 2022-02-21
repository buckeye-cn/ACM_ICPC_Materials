// https://open.kattis.com/problems/stackingup

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int stk[2000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> stk[i];
    }

    int offset = 0;
    string s;

    while (n) {
        n -= 1;
        stk[n] += offset;

        while (stk[n] > 1) {
            if (stk[n] % 2) {
                s += "+1+d";
                offset += 2;
            } else {
                s += "+d";
                offset += 1;
            }

            stk[n] /= 2;
        }

        s += '1';
    }

    for (int i = s.size() - 1; i >= 0; --i) {
        cout << s[i];
    }

    cout << endl;

    return 0;
}
