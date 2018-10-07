// https://open.kattis.com/problems/froggie

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

    int l, w;
    cin >> l >> w;

    int offset[l];
    int interval[l];
    int speed[l];

    for (int i = 0; i < l; ++i) {
        cin >> offset[i] >> interval[i] >> speed[i];
    }

    int p;
    string str;
    cin >> p >> str;

    int x = p;
    int y = l;

    bool safe = true;

    for (int i = 1; i <= str.size(); ++i) {
        if (str[i - 1] == 'L') {
            x -= 1;
        } else if (str[i - 1] == 'R') {
            x += 1;
        } else if (str[i - 1] == 'U') {
            y -= 1;
        } else if (str[i - 1] == 'D') {
            y += 1;
        }

        if (y < 0) continue;
        if (y >= l) continue;

        if (speed[y]) {
            int s = y & 1 ? -speed[y] : speed[y];
            int o = offset[y] + i * s - x;
            int k = o / (interval[y] * s) - (o < 0);

            safe &= o - k * interval[y] * s < 0
                || o - k * interval[y] * s >= s;
            // cerr << x << ':' << y << endl;
            // cerr << o - k * interval[y] * s + x << endl;
            // cerr << o - k * interval[y] * s - s + x << endl;
        }
    }

    if (safe && (y < 0 || y >= l)) {
        cout << "safe" << endl;
    } else {
        cout << "squish" << endl;
    }

    return 0;
}
