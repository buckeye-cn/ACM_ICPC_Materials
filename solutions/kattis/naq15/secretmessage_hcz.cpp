// https://open.kattis.com/problems/secretmessage

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

        int w = 0;
        while (w * w < s.size()) ++w;

        for (int j = 0; j < w; ++j) {
            for (int i = w - 1; i >= 0; --i) {
                if (i * w + j < s.size()) {
                    cout << s[i * w + j];
                }
            }
        }
        cout << endl;
    }

    return 0;
}
