// https://open.kattis.com/problems/flexible

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int w, p;
int l[120];
bool possible[120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> w >> p;

    for (int i = 0; i < p; ++i) {
        cin >> l[i];
    }

    for (int i = 0; i < p; ++i) {
        for (int j = i + 1; j < p; ++j) {
            possible[l[j] - l[i]] = true;
        }

        possible[l[i]] = true;
        possible[w - l[i]] = true;
    }

    for (int i = 0; i < w; ++i) {
        if (possible[i]) {
            cout << i << ' ';
        }
    }

    cout << w << endl;

    return 0;
}
