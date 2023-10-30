// https://open.kattis.com/problems/apivotalquestion

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int lx[1000000];
int rx[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;

        lx[i] = v;
        rx[i] = v;
    }

    for (int i = 0; i < n - 1; ++i) {
        lx[i + 1] = max(lx[i + 1], lx[i]);
    }

    for (int i = n - 1; i > 0; --i) {
        rx[i - 1] = min(rx[i - 1], rx[i]);
    }

    int nn = 0;

    for (int i = 0; i < n; ++i) {
        nn += lx[i] == rx[i];
    }

    cout << nn;

    nn = min(nn, 100);

    for (int i = 0; i < n; ++i) {
        if (lx[i] == rx[i]) {
            cout << ' ' << lx[i];

            nn -= 1;
            if (!nn) break;
        }
    }

    cout << endl;

    return 0;
}
