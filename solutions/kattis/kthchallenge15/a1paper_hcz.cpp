// https://open.kattis.com/problems/a1paper

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

    double len = 0;
    int need = 2;

    for (int i = 1; i < n; ++i) {
        int a;
        cin >> a;

        len += pow(2, -0.25 - 0.5 * i) * need / 2;
        need = max(need - a, 0) * 2;
    }

    if (need) {
        cout << "impossible" << endl;
    } else {
        cout << len << endl;
    }

    return 0;
}
