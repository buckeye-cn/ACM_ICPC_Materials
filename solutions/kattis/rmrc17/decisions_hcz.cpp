// https://open.kattis.com/problems/decisions

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int16_t fact[1 << 19];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    cin.ignore();
    cin.putback(' ');
    cin.read((char *) &fact[1 << n], 2 << n);

    int count = (2 << n) - 1;

    for (int m = n - 1; m >= 0; --m) {
        for (int i = 1 << m; i < 2 << m; ++i) {
            if (fact[i ^ (3 << m)] && fact[i ^ (3 << m)] == fact[i ^ (2 << m)]) {
                fact[i] = fact[i ^ (3 << m)];
                count -= 2;
            }
        }
    }

    cout << count << endl;

    return 0;
}
