// https://open.kattis.com/problems/buttonbashing

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int step[3601];
int bfs_q[4096];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int n, t;
        cin >> n >> t;

        int b[n];

        for (int j = 0; j < n; ++j) {
            cin >> b[j];
        }

        step[0] = 0;
        for (int j = 1; j <= 3600; ++j) {
            step[j] = 1e6;
        }

        int head = 0;
        int tail = 1;

        bfs_q[0] = 0;

        while (head < tail) {
            int p = bfs_q[head++ & 0xfff];

            for (int j = 0; j < n; ++j) {
                int pp = min(max(p + b[j], 0), 3600);

                if (step[pp] > step[p] + 1) {
                    step[pp] = step[p] + 1;
                    bfs_q[tail++ & 0xfff] = pp;
                }
            }
        }

        for (int j = t; j <= 3600; ++j) {
            if (step[j] < 1e6) {
                cout << step[j] << ' ' << j - t << endl;
                break;
            }
        }
    }

    return 0;
}
