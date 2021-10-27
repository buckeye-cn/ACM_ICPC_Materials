// https://open.kattis.com/problems/encodedmessage

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

        int m = sqrt(s.size());
        string ss;

        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                ss.push_back(s[k * m + m - j - 1]);
            }
        }

        cout << ss << endl;
    }

    return 0;
}
