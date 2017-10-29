/*
ID: hu.13381
PROG: transform
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
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

    int n;
    char mat[8][20][20];
    bool ok[8] = {true, true, true, true, true, true, true, true};

    fin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            fin >> c;
            mat[0][i][j] = c;
            mat[1][j][n-i-1] = c;
            mat[2][n-i-1][n-j-1] = c;
            mat[3][n-j-1][i] = c;
            mat[4][i][n-j-1] = c;
            mat[5][j][i] = c;
            mat[6][n-i-1][j] = c;
            mat[7][n-j-1][n-i-1] = c;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            fin >> c;
            cout << c << ':';
            for (int k = 0; k < 8; ++k) {
                cout << mat[k][i][j];
                if (c != mat[k][i][j]) {
                    ok[k] = false;
                }
            }
            cout << endl;
        }
    }

    if (ok[1]) {
        fout << 1 << endl;
    } else if (ok[2]) {
        fout << 2 << endl;
    } else if (ok[3]) {
        fout << 3 << endl;
    } else if (ok[4]) {
        fout << 4 << endl;
    } else if (ok[5] || ok[6] || ok[7]) {
        fout << 5 << endl;
    } else if (ok[0]) {
        fout << 6 << endl;
    } else {
        fout << 7 << endl;
    }

    return 0;
}
