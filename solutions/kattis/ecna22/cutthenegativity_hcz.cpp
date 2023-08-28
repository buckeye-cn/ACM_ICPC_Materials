// https://open.kattis.com/problems/cutthenegativity

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int nn = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> v[i][j];

            if (v[i][j] >= 0) {
                nn += 1;
            }
        }
    }

    cout << nn << endl;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (v[i][j] >= 0) {
                cout << i << ' ' << j << ' ' << v[i][j] << endl;
            }
        }
    }

    return 0;
}
