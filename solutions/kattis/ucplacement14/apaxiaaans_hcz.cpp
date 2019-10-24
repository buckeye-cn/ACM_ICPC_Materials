// https://open.kattis.com/problems/apaxiaaans

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

    string s;
    cin >> s;

    char last = 0;

    for (char c: s) {
        if (last != c) {
            last = c;
            cout << c;
        }
    }
    cout << endl;

    return 0;
}
