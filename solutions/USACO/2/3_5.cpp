/*
ID: hu.13381
PROG: concom
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

using namespace std;

int hold[101][101];
bool ctrl[101][101];

int main() {
    ofstream fout ("concom.out");
    ifstream fin ("concom.in");

    int n;
    fin >> n;
    for (int c = 0; c < n; ++c) {
        int i, j, p;
        fin >> i >> j >> p;
        hold[i][j] = p;
    }

    for (int i = 1; i <= 100; ++i) {
        ctrl[i][i] = true;
    }

    bool loop = true;
    while (loop) {
        loop = false;
        for (int i = 1; i <= 100; ++i) {
            for (int j = 1; j <= 100; ++j) {
                if (i == j) continue;
                if (ctrl[i][j]) continue;

                int h = 0;
                for (int k = 1; k <= 100; ++k) {
                    if (ctrl[i][k]) {
                        h += hold[k][j];
                    }
                }
                if (h > 50) {
                    ctrl[i][j] = true;
                    loop = true;
                }
            }
        }
    }

    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= 100; ++j) {
            if (i == j) continue;
            if (ctrl[i][j]) fout << i << ' ' << j << endl;
        }
    }

    return 0;
}
