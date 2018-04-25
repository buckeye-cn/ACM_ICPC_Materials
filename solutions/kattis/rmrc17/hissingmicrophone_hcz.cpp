// https://open.kattis.com/problems/hissingmicrophone

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

    for (int i = 1; i < s.size(); ++i) {
        if (s[i - 1] == 's' && s[i] == 's') {
            cout << "hiss" << endl;

            return 0;
        }
    }

    cout << "no hiss" << endl;

    return 0;
}
