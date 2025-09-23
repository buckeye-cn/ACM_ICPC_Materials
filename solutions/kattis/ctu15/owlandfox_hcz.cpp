// https://open.kattis.com/problems/owlandfox

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;

        if (n % 100000 == 0) {
            n -= 100000;
        } else if (n % 10000 == 0) {
            n -= 10000;
        } else if (n % 1000 == 0) {
            n -= 1000;
        } else if (n % 100 == 0) {
            n -= 100;
        } else if (n % 10 == 0) {
            n -= 10;
        } else {
            n -= 1;
        }

        cout << n << endl;
    }

    return 0;
}
