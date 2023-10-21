// https://open.kattis.com/problems/kinarow

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char mapdata[200][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int l;
    cin >> l;

    int xwin = 0;
    int owin = 0;

    for (; l > 0; --l) {
        int m, n, r;
        cin >> m >> n >> r;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> mapdata[i][j];
            }
        }

        bool xx = false;
        bool oo = false;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m - r + 1; ++j) {
                char now = mapdata[i][j];

                for (int k = 1; k < r; ++k) {
                    if (mapdata[i][j + k] != now) now = '.';
                }

                if (now == 'x') xx = true;
                if (now == 'o') oo = true;
            }
        }

        for (int i = 0; i < n - r + 1; ++i) {
            for (int j = 0; j < m; ++j) {
                char now = mapdata[i][j];

                for (int k = 1; k < r; ++k) {
                    if (mapdata[i + k][j] != now) now = '.';
                }

                if (now == 'x') xx = true;
                if (now == 'o') oo = true;
            }
        }

        for (int i = 0; i < n - r + 1; ++i) {
            for (int j = r - 1; j < m; ++j) {
                char now = mapdata[i][j];

                for (int k = 1; k < r; ++k) {
                    if (mapdata[i + k][j - k] != now) now = '.';
                }

                if (now == 'x') xx = true;
                if (now == 'o') oo = true;
            }
        }

        for (int i = 0; i < n - r + 1; ++i) {
            for (int j = 0; j < m - r + 1; ++j) {
                char now = mapdata[i][j];

                for (int k = 1; k < r; ++k) {
                    if (mapdata[i + k][j + k] != now) now = '.';
                }

                if (now == 'x') xx = true;
                if (now == 'o') oo = true;
            }
        }

        xwin += xx;
        owin += oo;
    }

    cout << xwin << ':' << owin << endl;

    return 0;
}
