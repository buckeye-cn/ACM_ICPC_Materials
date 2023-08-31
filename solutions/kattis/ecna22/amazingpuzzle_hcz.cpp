// https://open.kattis.com/problems/amazingpuzzle

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// n: r + 1
// e: c + 1
// s: r - 1
// w: c - 1
bool go[4][52][52];
int best[51][51][51][51];
char q[6250000][4];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int c, r, e;
    cin >> c >> r >> e;

    for (int i = 1; i <= c; ++i) {
        for (int j = 1; j <= r; ++j) {
            go[0][i][j] = j < r;
            go[1][i][j] = i < c;
            go[2][i][j] = j > 1;
            go[3][i][j] = i > 1;
        }
    }

    go[2][e][1] = true;

    int c1, r1, c2, r2;
    char d1, d2;
    cin >> c1 >> r1 >> d1 >> c2 >> r2 >> d2;

    if (d1 == 'N') d1 = 0;
    if (d1 == 'E') d1 = 1;
    if (d1 == 'S') d1 = 2;
    if (d1 == 'W') d1 = 3;
    if (d2 == 'N') d2 = 0;
    if (d2 == 'E') d2 = 1;
    if (d2 == 'S') d2 = 2;
    if (d2 == 'W') d2 = 3;

    int nn;
    cin >> nn;
    for (int i = 0; i < nn; ++i) {
        int cc, rr;
        cin >> cc >> rr;

        go[0][cc][rr] = false;
        go[2][cc][rr + 1] = false;
    }

    cin >> nn;
    for (int i = 0; i < nn; ++i) {
        int cc, rr;
        cin >> cc >> rr;

        go[1][cc][rr] = false;
        go[3][cc + 1][rr] = false;
    }

    int head = 0;
    int tail = 1;

    q[0][0] = c1;
    q[0][1] = r1;
    q[0][2] = c2;
    q[0][3] = r2;
    best[c1][r1][c2][r2] = 1;

    while (!best[e][0][e][0]) {
        for (int i = 0; i < 4; ++i) {
            char cc1 = q[head][0];
            char rr1 = q[head][1];
            char cc2 = q[head][2];
            char rr2 = q[head][3];
            int p1 = (d1 + i) & 3;
            int p2 = (d2 + i) & 3;
            int target = best[cc1][rr1][cc2][rr2] + 65536;

            if (rr1) {
                if (go[p1][cc1][rr1]) {
                    rr1 += p1 == 0;
                    cc1 += p1 == 1;
                    rr1 -= p1 == 2;
                    cc1 -= p1 == 3;
                } else {
                    target += 1;
                }
            }

            if (rr2) {
                if (go[p2][cc2][rr2]) {
                    rr2 += p2 == 0;
                    cc2 += p2 == 1;
                    rr2 -= p2 == 2;
                    cc2 -= p2 == 3;
                } else {
                    target += 1;
                }
            }

            if (cc1 != cc2 || rr1 != rr2 || (!rr1 && !rr2)) {
                int &b = best[cc1][rr1][cc2][rr2];

                if (!b || b > target) {
                    q[tail][0] = cc1;
                    q[tail][1] = rr1;
                    q[tail][2] = cc2;
                    q[tail][3] = rr2;
                    b = target;
                    tail += 1;
                }
            }
        }

        head += 1;
    }

    cout << (best[e][0][e][0] >> 16) << ' ' << (best[e][0][e][0] & 65535) - 1 << endl;

    return 0;
}
