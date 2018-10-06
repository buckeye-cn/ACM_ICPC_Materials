// https://open.kattis.com/problems/loopytransit

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool route[9][9];
int count[9];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        int from, to;
        cin >> from >> to;

        route[from][to] = true;
    }

    for (int p0 = 0; p0 < m; ++p0) {
        for (int p1 = 0; p1 < m; ++p1) {
            if (!route[p0][p1]) continue;
            if (p1 == p0) continue;
            count[1] += route[p1][p0];
            for (int p2 = 0; p2 < m; ++p2) {
                if (!route[p1][p2]) continue;
                if (p2 == p0) continue;
                if (p2 == p1) continue;
                count[2] += route[p2][p0];
                for (int p3 = 0; p3 < m; ++p3) {
                    if (!route[p2][p3]) continue;
                    if (p3 == p0) continue;
                    if (p3 == p1) continue;
                    if (p3 == p2) continue;
                    count[3] += route[p3][p0];
                    for (int p4 = 0; p4 < m; ++p4) {
                        if (!route[p3][p4]) continue;
                        if (p4 == p0) continue;
                        if (p4 == p1) continue;
                        if (p4 == p2) continue;
                        if (p4 == p3) continue;
                        count[4] += route[p4][p0];
                        for (int p5 = 0; p5 < m; ++p5) {
                            if (!route[p4][p5]) continue;
                            if (p5 == p0) continue;
                            if (p5 == p1) continue;
                            if (p5 == p2) continue;
                            if (p5 == p3) continue;
                            if (p5 == p4) continue;
                            count[5] += route[p5][p0];
                            for (int p6 = 0; p6 < m; ++p6) {
                                if (!route[p5][p6]) continue;
                                if (p6 == p0) continue;
                                if (p6 == p1) continue;
                                if (p6 == p2) continue;
                                if (p6 == p3) continue;
                                if (p6 == p4) continue;
                                if (p6 == p5) continue;
                                count[6] += route[p6][p0];
                                for (int p7 = 0; p7 < m; ++p7) {
                                    if (!route[p6][p7]) continue;
                                    if (p7 == p0) continue;
                                    if (p7 == p1) continue;
                                    if (p7 == p2) continue;
                                    if (p7 == p3) continue;
                                    if (p7 == p4) continue;
                                    if (p7 == p5) continue;
                                    if (p7 == p6) continue;
                                    count[7] += route[p7][p0];
                                    for (int p8 = 0; p8 < m; ++p8) {
                                        if (!route[p7][p8]) continue;
                                        if (p8 == p0) continue;
                                        if (p8 == p1) continue;
                                        if (p8 == p2) continue;
                                        if (p8 == p3) continue;
                                        if (p8 == p4) continue;
                                        if (p8 == p5) continue;
                                        if (p8 == p6) continue;
                                        if (p8 == p7) continue;
                                        count[8] += route[p8][p0];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int result = 0;

    for (int i = 1; i <= 8; ++i) {
        result += count[i] / (i + 1);
    }

    cout << result << endl;

    return 0;
}
