// https://open.kattis.com/problems/tictacstate

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
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int mask;
        cin >> oct >> mask;

        if (
            ((~mask | (mask >> 9)) & ((1 << 0) | (1 << 1) | (1 << 2))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 3) | (1 << 4) | (1 << 5))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 6) | (1 << 7) | (1 << 8))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 0) | (1 << 3) | (1 << 6))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 1) | (1 << 4) | (1 << 7))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 2) | (1 << 5) | (1 << 8))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 0) | (1 << 4) | (1 << 8))) == 0
            || ((~mask | (mask >> 9)) & ((1 << 2) | (1 << 4) | (1 << 6))) == 0
        ) {
            cout << "O wins" << endl;
        } else if (
            (~(mask >> 9) & ((1 << 0) | (1 << 1) | (1 << 2))) == 0
            || (~(mask >> 9) & ((1 << 3) | (1 << 4) | (1 << 5))) == 0
            || (~(mask >> 9) & ((1 << 6) | (1 << 7) | (1 << 8))) == 0
            || (~(mask >> 9) & ((1 << 0) | (1 << 3) | (1 << 6))) == 0
            || (~(mask >> 9) & ((1 << 1) | (1 << 4) | (1 << 7))) == 0
            || (~(mask >> 9) & ((1 << 2) | (1 << 5) | (1 << 8))) == 0
            || (~(mask >> 9) & ((1 << 0) | (1 << 4) | (1 << 8))) == 0
            || (~(mask >> 9) & ((1 << 2) | (1 << 4) | (1 << 6))) == 0
        ) {
            cout << "X wins" << endl;
        } else if ((mask & 511) == 511) {
            cout << "Cat's" << endl;
        } else {
            cout << "In progress" << endl;
        }
    }

    return 0;
}
