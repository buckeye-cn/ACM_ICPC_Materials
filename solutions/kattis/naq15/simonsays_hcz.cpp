// https://open.kattis.com/problems/simonsays

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
    cin.get();

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);

        if (s.substr(0, 11) == "Simon says ") {
            cout << s.substr(11, s.size()) << endl;
        }
    }

    return 0;
}
