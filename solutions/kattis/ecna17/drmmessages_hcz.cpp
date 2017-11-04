// https://open.kattis.com/problems/drmmessages

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
    string s2;

    int sum1 = 0;
    for (int i = 0; i < s.length() / 2; ++i) {
        sum1 += s[i] - 'A';
    }
    for (int i = 0; i < s.length() / 2; ++i) {
        s[i] = (s[i] - 'A' + sum1) % 26 + 'A';
    }
    int sum2 = 0;
    for (int i = s.length() / 2; i < s.length(); ++i) {
        sum2 += s[i] - 'A';
    }
    for (int i = s.length() / 2; i < s.length(); ++i) {
        s[i] = (s[i] - 'A' + sum2) % 26 + 'A';
    }

    s2.resize(s.length() / 2);
    for (int i = 0; i < s.length() / 2; ++i) {
        s2[i] = (int(s[i] - 'A') + int(s[i + s.length() / 2] - 'A')) % 26 + 'A';
    }

    cout << s2 << endl;

    return 0;
}
