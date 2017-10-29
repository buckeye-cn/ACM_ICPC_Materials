/*
ID: hu.13381
PROG: ttwo
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

bool did[10][10][4][10][10][4];

int main() {
    ofstream fout ("ttwo.out");
    ifstream fin ("ttwo.in");

    string s[10];
    int c_i, c_j, c_d, f_i, f_j, f_d;

    for (int i = 0; i < 10; ++i) {
        fin >> s[i];
        for (int j = 0; j < 10; ++j) {
            if (s[i][j] == 'C') {
                s[i][j] = '.';
                c_i = i;
                c_j = j;
            }
            if (s[i][j] == 'F') {
                s[i][j] = '.';
                f_i = i;
                f_j = j;
            }
        }
    }
    c_d = 0;
    f_d = 0;

    int step = 0;

    while (!did[c_i][c_j][c_d][f_i][f_j][f_d]) {
        did[c_i][c_j][c_d][f_i][f_j][f_d] = true;

        if (c_i == f_i && c_j == f_j) {
            fout << step << endl;
            return 0;
        }
        step += 1;

        auto func = [&](int &i, int &j, int &d) {
            switch (d) {
                case 0:
                    if (i == 0 || s[i - 1][j] == '*') {
                        d = 1;
                    } else {
                        i -= 1;
                    }
                    break;
                case 1:
                    if (j == 9 || s[i][j + 1] == '*') {
                        d = 2;
                    } else {
                        j += 1;
                    }
                    break;
                case 2:
                    if (i == 9 || s[i + 1][j] == '*') {
                        d = 3;
                    } else {
                        i += 1;
                    }
                    break;
                case 3:
                    if (j == 0 || s[i][j - 1] == '*') {
                        d = 0;
                    } else {
                        j -= 1;
                    }
                    break;
            }
        };

        func(c_i, c_j, c_d);
        func(f_i, f_j, f_d);

        cout << c_i << ' ' << c_j << " - ";
        cout << f_i << ' ' << f_j << endl;
    }

    fout << 0 << endl;
    return 0;
}
