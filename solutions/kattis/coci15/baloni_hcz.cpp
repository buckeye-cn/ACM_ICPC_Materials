// https://open.kattis.com/problems/baloni

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int h[1000000];
int arrow[1000002];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    for (int i = n - 1; i >= 0; --i) {
        if (arrow[h[i]]) {
            n -= 1;
            arrow[h[i]] -= 1;
        }

        arrow[h[i] + 1] += 1;
    }

    cout << n << endl;

    return 0;
}
