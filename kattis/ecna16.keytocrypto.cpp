// https://ecna16.kattis.com/problems/ecna16.keytocrypto

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
    cout.precision(10);

    string a, b;
    cin >> a >> b;

    for (int i = 0; i < a.size(); ++i) {
        char c = char(((a[i] - 'A') - (b[i] - 'A') + 26) % 26 + 'A');
        b += c;
        cout << c;
    }

    cout << endl;

    return 0;
}
