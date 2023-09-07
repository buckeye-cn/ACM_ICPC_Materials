// https://open.kattis.com/problems/harshadnumbers

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

    while (true) {
        int t = 0;

        for (int i = n; i; i /= 10) {
            t += i % 10;
        }

        if (!(n % t)) {
            break;
        }

        ++n;
    }

    cout << n << endl;

    return 0;
}
