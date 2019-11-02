// https://open.kattis.com/problems/cardboardcontainer

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

    int v;
    cin >> v;

    int best = v * 4 + 2;

    for (int i = 1; i * i * i <= v; ++i) {
        if (v % i) continue;

        for (int j = i; i * j * j <= v; ++j) {
            if (v % (i * j)) continue;

            int k = v / (i * j);

            best = min(best, 2 * i * j + 2 * j * k + 2 * k * i);
        }
    }

    cout << best << endl;

    return 0;
}
