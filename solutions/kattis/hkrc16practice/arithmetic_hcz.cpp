// https://open.kattis.com/problems/arithmetic

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define HEX "0123456789ABCDEF"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;
    cin >> s;

    if (s == "0") {
        cout << "0" << endl;

        return 0;
    }

    int head_len = s.size() - (s.size() - 1) / 4 * 4;

    int head_val = 0;
    string head_str;

    for (int i = 0; i < head_len; ++i) {
        head_val *= 8;
        head_val += s[i] - '0';
    }

    while (head_val) {
        head_str = (HEX[head_val % 16]) + head_str;
        head_val /= 16;
    }

    cout << head_str;

    for (int i = head_len; i < s.size(); i += 4) {
        int val = ((s[i    ] - '0') << 9)
                + ((s[i + 1] - '0') << 6)
                + ((s[i + 2] - '0') << 3)
                + ((s[i + 3] - '0'));

        cout << HEX[val >> 8] << HEX[(val >> 4) & 15] << HEX[val & 15];
    }

    cout << endl;

    return 0;
}
