// https://open.kattis.com/problems/hrpa

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

long fib[72];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    fib[0] = 1;
    fib[1] = 2;

    for (int i = 2; i < 72; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    long n;
    cin >> n;

    for (int i = 71; i >= 0; --i) {
        if (n == fib[i]) {
            break;
        }

        if (n > fib[i]) {
            n -= fib[i];
        }
    }

    cout << n << endl;

    return 0;
}
