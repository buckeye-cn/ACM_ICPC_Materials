// https://open.kattis.com/problems/8queens

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool used[8][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int count = 0;
    bool ok = true;

    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            char c;
            cin >> c;

            if (c == '*') {
                for (int u = -1; u <= 1; ++u) {
                    for (int v = -1; v <= 1; ++v) {
                        if (!u && !v) continue;

                        int x = i;
                        int y = j;

                        while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
                            ok &= !used[x][y];
                            x += u;
                            y += v;
                        }
                    }
                }

                count += 1;
                used[i][j] = true;
            }
        }
    }

    ok &= count == 8;

    cout << (ok ? "valid" : "invalid") << endl;

    return 0;
}
