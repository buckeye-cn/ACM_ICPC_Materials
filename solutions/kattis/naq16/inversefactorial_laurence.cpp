#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    unsigned long long pref = stoull(s.substr(0, 10));

    double prefix = 1;
    for (int i = 1; i < 205025; i++) {
        prefix *= i;
        while (prefix > 1e10)
            prefix /= 10;
        if ((unsigned long long)floor(prefix) == pref)
            cout << i << endl;
    }
}
