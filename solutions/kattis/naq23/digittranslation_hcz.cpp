// https://open.kattis.com/problems/digittranslation

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp_l[1000001];
int dp_c[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    dp_c[0] = 1;

    for (int i = 0; i < s.size(); ++i) {
        dp_l[i + 1] = dp_l[i] + 1;
        dp_c[i + 1] = dp_c[i];

        int v = 0;

        if (i >= 3 && s[i - 3] == 'z' && s[i - 2] == 'e' && s[i - 1] == 'r' && s[i] == 'o') v = 4;
        if (i >= 2 && s[i - 2] == 'o' && s[i - 1] == 'n' && s[i] == 'e') v = 3;
        if (i >= 2 && s[i - 2] == 't' && s[i - 1] == 'w' && s[i] == 'o') v = 3;
        if (i >= 4 && s[i - 4] == 't' && s[i - 3] == 'h' && s[i - 2] == 'r' && s[i - 1] == 'e' && s[i] == 'e') v = 5;
        if (i >= 3 && s[i - 3] == 'f' && s[i - 2] == 'o' && s[i - 1] == 'u' && s[i] == 'r') v = 4;
        if (i >= 3 && s[i - 3] == 'f' && s[i - 2] == 'i' && s[i - 1] == 'v' && s[i] == 'e') v = 4;
        if (i >= 2 && s[i - 2] == 's' && s[i - 1] == 'i' && s[i] == 'x') v = 3;
        if (i >= 4 && s[i - 4] == 's' && s[i - 3] == 'e' && s[i - 2] == 'v' && s[i - 1] == 'e' && s[i] == 'n') v = 5;
        if (i >= 4 && s[i - 4] == 'e' && s[i - 3] == 'i' && s[i - 2] == 'g' && s[i - 1] == 'h' && s[i] == 't') v = 5;
        if (i >= 3 && s[i - 3] == 'n' && s[i - 2] == 'i' && s[i - 1] == 'n' && s[i] == 'e') v = 4;

        if (v) {
            if (dp_l[i + 1] > dp_l[i + 1 - v] + 1) {
                dp_l[i + 1] = dp_l[i + 1 - v] + 1;
                dp_c[i + 1] = dp_c[i + 1 - v];
            } else if (dp_l[i + 1] == dp_l[i + 1 - v] + 1) {
                dp_c[i + 1] += dp_c[i + 1 - v];
                dp_c[i + 1] %= 9302023;
            }
        }

        // cerr << v << ' ' << dp_l[i + 1] << ' ' << dp_c[i + 1] << endl;
    }

    cout << dp_l[s.size()] << endl;
    cout << dp_c[s.size()] << endl;

    return 0;
}
