// https://open.kattis.com/problems/circuitmath

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

    bool value[n];
    char c;

    for (int i = 0; i < n; ++i) {
        cin >> c;

        value[i] = c == 'T';
    }

    int tail = 0;
    bool stack[1000];

    while (cin >> c) {
        if (c == '*') {
            stack[tail - 2] &= stack[tail - 1];
            tail -= 1;
        } else if (c == '+') {
            stack[tail - 2] |= stack[tail - 1];
            tail -= 1;
        } else if (c == '-') {
            stack[tail - 1] = !stack[tail - 1];
        } else {
            stack[tail] = value[c - 'A'];
            tail += 1;
        }
    }

    if (stack[0]) {
        cout << 'T' << endl;
    } else {
        cout << 'F' << endl;
    }

    return 0;
}
