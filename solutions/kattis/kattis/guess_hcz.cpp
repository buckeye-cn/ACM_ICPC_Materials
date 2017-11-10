// https://open.kattis.com/problems/guess

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

    int value = 0;

    for (int i = 9; i >= 0; --i) {
        int new_value = min(value | (1 << i), 1000);

        cout << new_value << endl;

        string s;
        cin >> s;

        if (s[0] == 'l') {
            // nothing
        } else if (s[0] == 'h') {
            value = new_value;
        } else {
            return 0;
        }
    }

    cout << value << endl;

    return 0;
}
