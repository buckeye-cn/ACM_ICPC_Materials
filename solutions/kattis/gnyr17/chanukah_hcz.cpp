// https://open.kattis.com/problems/chanukah

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

    int p;
    cin >> p;

    for (int i = 0; i < p; ++i) {
        int k, n;
        cin >> k >> n;

        cout << k << ' ' << n * (n + 3) / 2 << endl;
    }

    return 0;
}
