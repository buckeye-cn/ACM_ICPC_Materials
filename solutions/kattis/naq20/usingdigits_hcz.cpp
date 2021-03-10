// https://open.kattis.com/problems/usingdigits

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char v[101][101];
char h[51];
int best[101][101][51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int x, y;
    string s;
    cin >> x >> y >> s;

    h[0] = -1;

    for (int i = 1; i <= s.size(); ++i) {
        h[i] = s[i - 1] - '0';
    }

    for (int i = y; i >= 1; --i) {
        cin >> s;

        for (int j = 1; j <= x; ++j) {
            v[i][j] = s[j - 1] - '0';
        }
    }

    best[0][1][0] = -100000;

    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            for (int k = 0; h[k]; ++k) {
                best[i][j][k] = min(best[i - 1][j][k], best[i][j - 1][k]);

                if (k && i - h[k] >= 2) {
                    best[i][j][k] = min(best[i][j][k], best[i - h[k] - 1][j][k - 1]);
                }

                if (k && j - h[k] >= 2) {
                    best[i][j][k] = min(best[i][j][k], best[i][j - h[k] - 1][k - 1]);
                }

                best[i][j][k] += v[i][j];
            }
        }
    }

    int result = 0;

    for (int k = 0; h[k]; ++k) {
        result = min(result, best[y][x][k]);
    }

    cout << result + 100000 << endl;

    return 0;
}
