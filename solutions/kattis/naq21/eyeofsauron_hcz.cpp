// https://open.kattis.com/problems/eyeofsauron

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

    for (int i = 0; i < s.size(); ++i) {
        if ((s[i] == '|') != (s[s.size() - 1 - i] == '|')) {
            cout << "fix" << endl;

            return 0;
        }
    }

    cout << "correct" << endl;

    return 0;
}
