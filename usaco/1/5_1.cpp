/*
ID: hu.13381
PROG: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");

    int c;
    fin >> c;

    int data[1024][1024];
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j <= i; ++j) {
            int x;
            fin >> x;
            data[i][j] = x;
        }
    }
    for (int i = c - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            if (data[i + 1][j] > data[i + 1][j + 1]) {
                data[i][j] += data[i + 1][j];
            } else {
                data[i][j] += data[i + 1][j + 1];
            }
        }
    }

    fout << data[0][0] << endl;

    return 0;
}
