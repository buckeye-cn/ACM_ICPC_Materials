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

    int w, h;
    cin >> w >> h;

    cin.get();

    string s;
    getline(cin, s);

    for (int i = 0; i < h && i * w < s.size(); ++i) {
        for (int j = 0; j < w && i * w + j < s.size(); ++j) {
            cout << s[i * w + j];
        }
        cout << endl;
    }

    return 0;
}
