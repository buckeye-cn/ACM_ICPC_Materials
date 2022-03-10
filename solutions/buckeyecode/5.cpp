#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int sp;
long v[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        if (s == "+") {
            sp -= 1;
            v[sp] += v[sp + 1];
        } else if (s == "-") {
            sp -= 1;
            v[sp] -= v[sp + 1];
        } else if (s == "*") {
            sp -= 1;
            v[sp] *= v[sp + 1];
        } else if (s == "/") {
            sp -= 1;
            v[sp] /= v[sp + 1];
        } else if (s == "swap") {
            swap(v[sp - 1], v[sp]);
        } else if (s == "enter") {
            sp += 1;
            v[sp] = v[sp - 1];
        } else {
            v[sp] = stoi(s);
        }
    }

    cout << v[sp] << endl;

    return 0;
}
