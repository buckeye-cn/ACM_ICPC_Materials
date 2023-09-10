// https://open.kattis.com/problems/catmouse

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

    for (int i = 0; i < n; ++i) {
        int r, t, j;
        cin >> r >> t >> j;
        // a + pi = tan(a)
        // k = cos(a)
        cout << (t * 4.603339 >= j ? "YES" : "NO") << endl;
    }

    return 0;
}
