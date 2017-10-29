/*
ID: hu.13381
PROG: cowtour
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    ofstream fout ("cowtour.out");
    ifstream fin ("cowtour.in");

    int n;
    int pos[200][2];
    double dist[200][200];
    double rdist[200][200];

    #define sqr(x) ((x) * (x))

    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> pos[i][0] >> pos[i][1];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rdist[i][j] = sqrt(
                sqr(pos[i][0] - pos[j][0])
                + sqr(pos[i][1] - pos[j][1])
            );

            char c;
            fin >> c;
            if (i == j) {
                dist[i][j] = 0;
            } else if (c == '1') {
                dist[i][j] = rdist[i][j];
            } else {
                dist[i][j] = 1e20;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    double ijmax = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] > 1e19) continue;
            if (ijmax < dist[i][j]) {
                ijmax = dist[i][j];
            }
        }
    }

    double xdist = 1e20;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dist[i][j] << '\t';

            if (dist[i][j] < 1e19) continue;
            double x1 = 0;
            double x2 = 0;
            for (int k = 0; k < n; ++k) {
                if (dist[i][k] > 1e19 && dist[j][k] > 1e19) continue;
                if (dist[i][k] < dist[j][k]) {
                    if (x1 < dist[i][k]) {
                        x1 = dist[i][k];
                    }
                } else {
                    if (x2 < dist[j][k]) {
                        x2 = dist[j][k];
                    }
                }
            }
            double xx = x1 + x2 + rdist[i][j];
            if (xdist > xx) {
                xdist = xx;
            }
        }
        cout << endl;
    }

    if (xdist < ijmax) {
        xdist = ijmax;
    }

    FILE *f = fopen("cowtour.out", "w");
    fprintf(f, "%.6f\n", xdist);

    return 0;
}
