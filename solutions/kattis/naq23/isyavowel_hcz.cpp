// https://open.kattis.com/problems/isyavowel

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

    int aeiou = 0;
    int y = 0;

    for (char c: s) {
        aeiou += c == 'a';
        aeiou += c == 'e';
        aeiou += c == 'i';
        aeiou += c == 'o';
        aeiou += c == 'u';
        y += c == 'y';
    }

    cout << aeiou << ' ' << aeiou + y << endl;

    return 0;
}
