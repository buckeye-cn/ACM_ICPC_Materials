/*
ID: hu.13381
PROG: comehome
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
    ofstream fout ("comehome.out");
    ifstream fin ("comehome.in");

    int n;
    fin >> n;

    int dist[256][256];
    bool cow[256];

    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            dist[i][j] = 100000000;
        }
        cow[i] = false;
    }

    for (int i = 0; i < n; ++i) {
        char a, b;
        fin >> a >> b;
        if (a < 'Z') {
            cow[int(a)] = true;
        }
        if (b < 'Z') {
            cow[int(b)] = true;
        }
        int d;
        fin >> d;
        if (dist[int(a)][int(b)] > d) {
            dist[int(a)][int(b)] = d;
            dist[int(b)][int(a)] = d;
        }
    }

    for (int k = 0; k < 256; ++k) {
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 256; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    char xa;
    int xd = 100000000;

    for (int i = 0; i < 256; ++i) {
        if (cow[i] && xd > dist[i][int('Z')]) {
            xd = dist[i][int('Z')];
            xa = i;
        }
    }

    fout << xa << ' ' << xd << endl;

    return 0;
}
