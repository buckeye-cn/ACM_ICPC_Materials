// https://open.kattis.com/problems/classfieldtrip

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

    string s1, s2;
    cin >> s1 >> s2;

    for (char c = 'a'; c <= 'z'; ++c) {
        for (char c1: s1) {
            if (c1 == c) {
                cout << c;
            }
        }

        for (char c2: s2) {
            if (c2 == c) {
                cout << c;
            }
        }
    }

    cout << endl;

    return 0;
}
