// https://open.kattis.com/problems/buildinfences

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

    int x1 = 1e9;
    int x2 = 0;
    int y1 = 1e9;
    int y2 = 0;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        x1 = min(x1, x);
        x2 = max(x2, x);
        y1 = min(y1, y);
        y2 = max(y2, y);
    }

    cout << 2 * (x2 - x1 + y2 - y1 + 4) << endl;

    return 0;
}
