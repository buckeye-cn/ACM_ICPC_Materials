// https://open.kattis.com/problems/travelingmerchant

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[100000];
int d[100000];

int vv[7][100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> v[i] >> d[i];
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < n; ++j) {
            vv[i][j] = v[j] + d[j] * ("0123210"[(j - i + 7) % 7] - '0');
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int s, t;
        cin >> s >> t;

        s -= 1;
        t -= 1;

        int offset = s < t ? s % 7 : (s + 1) % 7;

        int curr_min = 1e9;
        int curr_best = 0;

        if (s < t) {
            for (int j = s; j <= t; ++j) {
                int price = vv[offset][j];

                curr_min = min(curr_min, price);
                curr_best = max(curr_best, price - curr_min);
            }
        } else {
            for (int j = s; j >= t; --j) {
                int price = vv[offset][j];

                curr_min = min(curr_min, price);
                curr_best = max(curr_best, price - curr_min);
            }
        }

        cout << curr_best << endl;
    }

    return 0;
}
