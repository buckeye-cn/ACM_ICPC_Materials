// https://open.kattis.com/problems/bottledup

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

    int s, v1, v2;
    cin >> s >> v1 >> v2;

    for (int i = s / v1 * v1; i >= 0; i -= v1) {
        if ((s - i) % v2 == 0) {
            cout << i / v1 << ' ' << (s - i) / v2 << endl;

            return 0;
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
