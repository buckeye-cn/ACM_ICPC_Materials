// https://open.kattis.com/problems/dst

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
        char c;
        int d, h, m;
        cin >> c >> d >> h >> m;

        if (c == 'B') {
            d = -d;
        }

        int t = (h + 24) * 60 + m + d;

        cout << (t / 60) % 24 << ' ' << t % 60 << endl;
    }

    return 0;
}
