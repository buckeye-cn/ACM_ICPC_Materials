// https://open.kattis.com/problems/aaah

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

    if (s1.size() >= s2.size()) {
        cout << "go" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
