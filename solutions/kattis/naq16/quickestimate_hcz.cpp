// https://open.kattis.com/problems/quickestimate

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

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        int result = s.size();

        for (char c: s) {
            if (c != '0') break;

            result -= 1;
        }

        if (result) {
            cout << result << endl;
        } else {
            cout << 1 << endl;
        }
    }

    return 0;
}
