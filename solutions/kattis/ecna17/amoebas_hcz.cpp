// https://open.kattis.com/problems/amoebas

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int m, n;

bool map1[200][200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> m >> n;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if (c == '#') {
                map1[i][j] = true;
            }
        }
    }

    int tot = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (map1[i][j]) {
                int x = i;
                int y = j;

                while (true) {
                    map1[x][y] = false;

                    bool ok = false;
                    for (int xx = x - 1; xx <= x + 1 && !ok; ++xx) {
                        for (int yy = y - 1; yy <= y + 1 && !ok; ++yy) {
                            if (map1[xx][yy]) {
                                x = xx;
                                y = yy;
                                ok = true;
                            }
                        }
                    }

                    if (!ok) break;
                }

                tot += 1;
            }
        }
    }

    cout << tot << endl;

    return 0;
}
