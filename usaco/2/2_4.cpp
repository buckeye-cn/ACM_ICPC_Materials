/*
ID: hu.13381
PROG: lamps
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

int main() {
    ofstream fout ("lamps.out");
    ifstream fin ("lamps.in");

    static const int data[8][7] = {
        {0, 0, 0, 0, 0, 0, /* step: */ 1},
        {0, 0, 1, 1, 1, 0, /* step: */ 2},
        {0, 1, 0, 1, 0, 1, /* step: */ 1},
        {0, 1, 1, 0, 1, 1, /* step: */ 1},
        {1, 0, 0, 1, 0, 0, /* step: */ 2},
        {1, 0, 1, 0, 1, 0, /* step: */ 1},
        {1, 1, 0, 0, 0, 1, /* step: */ 2},
        {1, 1, 1, 1, 1, 1, /* step: */ 0},
    };

    int n, c;
    fin >> n >> c;

    bool ok[8] = {true,true,true,true,true,true,true,true};

    for (int i = 0; i < 8; ++i) {
        if (data[i][6] > c) {
            ok[i] = false;
        }
    }

    while (1) {
        int x;
        fin >> x;
        if (x == -1) break;
        x = (x - 1) % 6;
        for (int i = 0; i < 8; ++i) {
            if (data[i][x] != 1) {
                ok[i] = false;
            }
        }
    }

    while (1) {
        int x;
        fin >> x;
        if (x == -1) break;
        x = (x - 1) % 6;
        for (int i = 0; i < 8; ++i) {
            if (data[i][x] != 0) {
                ok[i] = false;
            }
        }
    }

    bool ok1 = false;
    for (int i = 0; i < 8; ++i) {
        if (ok[i]) {
            for (int j = 0; j < n; ++j) {
                fout << (data[i][j % 6] ? '1' : '0');
            }
            fout << endl;
            ok1 = true;
        }
    }

    if (!ok1) {
        fout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
