// https://open.kattis.com/problems/waterjournal

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

    int n, a, b;
    cin >> n >> a >> b;

    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;

        if (a == w) a = -a;
        if (b == w) b = -b;
    }

    if (a > 0 && b > 0) {
        cout << -1 << endl;
    } else if (a > 0) {
        cout << a << endl;
    } else if (b > 0) {
        cout << b << endl;
    } else {
        for (int i = -a; i <= -b; ++i) {
            cout << i << endl;
        }
    }

    return 0;
}
