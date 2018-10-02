// https://open.kattis.com/problems/undetected

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

int n;
int m[201][301];

int q_head, q_tail;
pair<int, int> q[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    int i;

    for (i = 0; i < n; ++i) {
        int x, y, r;
        cin >> x >> y >> r;

        q_head = 0;
        q_tail = 0;

        for (int xx = 0; xx <= 200; ++xx) {
            q[q_tail++] = {xx, 0};
        }

        bool ok = false;

        while (q_head != q_tail) {
            pair<int, int> p = q[q_head++];

            if (m[p.first][p.second] != i) continue;
            if (sqr(p.first - x) + sqr(p.second - y) <= sqr(r)) continue;

            m[p.first][p.second] = i + 1;

            if (p.second == 300) {
                ok = true;
            }

            if (p.second < 300) {
                q[q_tail++] = {p.first, p.second + 1};
            }
            if (p.second > 0) {
                q[q_tail++] = {p.first, p.second - 1};
            }
            if (p.first < 200) {
                q[q_tail++] = {p.first + 1, p.second};
            }
            if (p.first > 0) {
                q[q_tail++] = {p.first - 1, p.second};
            }
        }

        // if (i == 0) {
        //     for (int yy = 0; yy <= 300; ++yy) {
        //         for (int xx = 0; xx <= 200; ++xx) {
        //             cerr << (m[xx][yy] == i + 1);
        //         }
        //         cerr << endl;
        //     }
        // }

        if (!ok) {
            break;
        }
    }

    cout << i << endl;

    return 0;
}
