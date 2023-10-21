// https://open.kattis.com/problems/multitouch

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

using namespace std;

string mapdata[2][15];

int pixels[2][5];
double ave_i[2][5];
double ave_j[2][5];

int touches[2];
double g_ave_i[2];
double g_ave_j[2];

void dfs(int d, int i, int j, int touch) {
    if (i < 0 || i >= 15) return;
    if (j < 0 || j >= 30) return;
    if (mapdata[d][i][j] != 'X') return;

    mapdata[d][i][j] = '0' + touch;

    ave_i[d][touch] += i;
    ave_j[d][touch] += j;
    pixels[d][touch] += 1;

    dfs(d, i, j - 1, touch);
    dfs(d, i, j + 1, touch);
    dfs(d, i - 1, j, touch);
    dfs(d, i + 1, j, touch);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 0; i < 15; ++i) {
        cin >> mapdata[0][i] >> mapdata[1][i];
    }

    for (int d = 0; d < 2; ++d) {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 30; ++j) {
                if (mapdata[d][i][j] == 'X') {
                    dfs(d, i, j, touches[d]);

                    ave_i[d][touches[d]] /= pixels[d][touches[d]];
                    ave_j[d][touches[d]] /= pixels[d][touches[d]];

                    g_ave_i[d] += ave_i[d][touches[d]];
                    g_ave_j[d] += ave_j[d][touches[d]];
                    touches[d] += 1;
                }
            }
        }

        g_ave_i[d] /= touches[d];
        g_ave_j[d] /= touches[d];
    }

    int mapping[5];
    int best_mapping[5];
    double best_delta = +INFINITY;

    for (mapping[0] = 0; mapping[0] < 5; ++mapping[0]) {
        for (mapping[1] = 0; mapping[1] < 5; ++mapping[1]) {
            if (mapping[1] == mapping[0]) continue;
            for (mapping[2] = 0; mapping[2] < 5; ++mapping[2]) {
                if (mapping[2] == mapping[0]) continue;
                if (mapping[2] == mapping[1]) continue;
                for (mapping[3] = 0; mapping[3] < 5; ++mapping[3]) {
                    if (mapping[3] == mapping[0]) continue;
                    if (mapping[3] == mapping[1]) continue;
                    if (mapping[3] == mapping[2]) continue;
                    for (mapping[4] = 0; mapping[4] < 5; ++mapping[4]) {
                        if (mapping[4] == mapping[0]) continue;
                        if (mapping[4] == mapping[1]) continue;
                        if (mapping[4] == mapping[2]) continue;
                        if (mapping[4] == mapping[3]) continue;

                        double tot_delta = 0;

                        for (int i = 0; i < touches[0]; ++i) {
                            if (mapping[i] >= touches[0]) tot_delta = +INFINITY;
                            tot_delta += sqr(ave_i[1][mapping[i]] - ave_i[0][i]) + sqr(ave_j[1][mapping[i]] - ave_j[0][i]);
                        }

                        if (best_delta > tot_delta) {
                            for (int i = 0; i < touches[0]; ++i) {
                                best_mapping[i] = mapping[i];
                            }

                            best_delta = tot_delta;
                        }
                    }
                }
            }
        }
    }

    double spread[2] {0, 0};

    for (int d = 0; d < 2; ++d) {
        for (int i = 0; i < touches[d]; ++i) {
            spread[d] += sqrt(sqr(ave_i[d][i] - g_ave_i[d]) + sqr(ave_j[d][i] - g_ave_j[d])) / touches[d];
        }
    }

    double gr = 0;

    for (int i = 0; i < touches[0]; ++i) {
        int j = best_mapping[i];

        double d0 = sqrt(sqr(ave_i[0][i] - g_ave_i[0]) + sqr(ave_j[0][i] - g_ave_j[0]));
        double d1 = sqrt(sqr(ave_i[1][j] - g_ave_i[1]) + sqr(ave_j[1][j] - g_ave_j[1]));
        double dot = (ave_i[0][i] - g_ave_i[0]) * (ave_i[1][j] - g_ave_i[1])
            + (ave_j[0][i] - g_ave_j[0]) * (ave_j[1][j] - g_ave_j[1]);
        double cross = (ave_i[0][i] - g_ave_i[0]) * (ave_j[1][j] - g_ave_j[1])
            - (ave_j[0][i] - g_ave_j[0]) * (ave_i[1][j] - g_ave_i[1]);

        gr += acos(dot / d0 / d1) * (cross > 0 ? 1 : -1) / touches[0];
    }

    double pan = sqrt(sqr(g_ave_i[1] - g_ave_i[0]) + sqr(g_ave_j[1] - g_ave_j[0]));

    double zoom = abs(spread[1] - spread[0]);

    double rotation = touches[0] > 1 ? abs(gr * spread[0]) : 0;

    // for (int i = 0; i < 15; ++i) {
    //     cerr << mapdata[0][i] << ' ' << mapdata[1][i] << endl;
    // }
    // cerr << pan << ' ' << zoom << ' ' << rotation << endl;

    if (pan > zoom && pan > rotation) {
        cout << touches[0] << " pan" << endl;
    } else if (zoom > rotation) {
        cout << touches[0] << " zoom " << (spread[1] > spread[0] ? "out" : "in") << endl;
    } else {
        cout << touches[0] << " rotate " << (gr > 0 ? "counter-clockwise" : "clockwise") << endl;
    }

    return 0;
}
