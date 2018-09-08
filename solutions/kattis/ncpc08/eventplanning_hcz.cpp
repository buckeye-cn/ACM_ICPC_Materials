// https://open.kattis.com/problems/eventplanning

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

    int n, b, h, w;
    cin >> n >> b >> h >> w;

    int best = b + 1;

    for (int i = 0; i < h; ++i) {
        int p;
        cin >> p;

        for (int j = 0; j < w; ++j) {
            int a;
            cin >> a;

            if (n <= a) {
                best = min(best, p * n);
            }
        }
    }

    if (best == b + 1) {
        cout << "stay home" << endl;
    } else {
        cout << best << endl;
    }

    return 0;
}
