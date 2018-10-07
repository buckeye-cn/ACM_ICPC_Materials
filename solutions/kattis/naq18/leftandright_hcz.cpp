// https://open.kattis.com/problems/leftandright

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

    string s;
    cin >> s;

    s = 'R' + s;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'R') {
            if (i == s.size() - 1 || s[i + 1] == 'R') {
                cout << i + 1 << endl;
            } else {
                int j;
                for (j = i + 1; j < s.size() && s[j] == 'L'; ++j);

                for (int k = i; k < j; ++k) {
                    cout << i + j - k << endl;
                }
            }
        }
    }

    return 0;
}
