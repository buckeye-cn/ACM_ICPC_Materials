// https://open.kattis.com/problems/usingdigits

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int16_t best[101][101][51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int x, y;
    string s;
    cin >> x >> y >> s;

    char h[s.size() + 1];

    for (int k = 1; k <= s.size(); ++k) {
        h[k] = s[k - 1] - '0';
    }

    char v[y + 1][x + 1];
    cin.read(&v[0][0], (x + 1) * y);

    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            v[y - i][j] -= '0';
        }
    }

    best[0][1][0] = -10000;

    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            for (int k = 0; k <= s.size(); ++k) {
                best[i][j][k] = min(best[i - 1][j][k], best[i][j - 1][k]);

                if (k && i - h[k] >= 2) {
                    best[i][j][k] = min(best[i][j][k], best[i - h[k] - 1][j][k - 1]);
                }

                if (k && j - h[k] >= 2) {
                    best[i][j][k] = min(best[i][j][k], best[i][j - h[k] - 1][k - 1]);
                }

                best[i][j][k] += v[y - i][j];
            }
        }
    }

    int16_t result = 0;

    for (int k = 0; k <= s.size(); ++k) {
        result = min(result, best[y][x][k]);
    }

    cout << result + 10000 << endl;

    return 0;
}
