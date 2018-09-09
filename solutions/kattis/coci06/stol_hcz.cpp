// https://open.kattis.com/problems/stol

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int r, s;
string room[1000];
int len[1000][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> r >> s;

    for (int i = 0; i < r; ++i) {
        cin >> room[i];

        int last = 0;
        for (int j = s - 1; j >= 0; --j) {
            if (room[i][j] == '.') {
                last += 1;
                len[i][j] = last;
            } else {
                last = 0;
            }
        }
    }

    int best = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            int w = len[i][j];

            for (int h = 1; h <= r - i && w && w + r - i > best; ++h) {
                best = max(best, w + h);
                w = min(w, len[i + h][j]);
            }
        }
    }

    cout << best * 2 - 1 << endl;

    return 0;
}
