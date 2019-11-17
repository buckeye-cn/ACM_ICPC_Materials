// https://open.kattis.com/problems/cokolada

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

    int k;
    cin >> k;

    int a, b;

    for (int i = 30; i >= 0; --i) {
        if ((1 << i) >= k) {
            a = i;
        }

        if ((1 << i) >= (k & -k)) {
            b = i;
        }
    }

    cout << (1 << a) << ' ' << a - b << endl;

    return 0;
}
