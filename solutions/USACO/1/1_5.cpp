/*
ID: hu.13381
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    int n;
    fin >> n;
    std::string s;
    fin >> s;

    char last_color = '?';
    int last_b = 0;
    int last_r = 0;
    int last_w = 0;
    int last = 0;
    int max = 0;
    for (int zz = 0; zz < 3; ++zz)
    for (int i = 0; i < n; ++i) {
        switch (s[i]) {
            case 'b':
                if (last_color == 'r') {
                    last = last_r - last_w;
                    last_b = last_w + 1;
                    last_r = 0;
                    last_w = 0;
                } else {
                    last_b += 1;
                    last_r = 0;
                    last_w = 0;
                }
                last_color = 'b';
                break;
            case 'r':
                if (last_color == 'b') {
                    last = last_b - last_w;
                    last_b = 0;
                    last_r = last_w + 1;
                    last_w = 0;
                } else {
                    last_b = 0;
                    last_r += 1;
                    last_w = 0;
                }
                last_color = 'r';
                break;
            case 'w':
                if (last_color == 'b') {
                    last_w += 1;
                    last_b += 1;
                } else {
                    last_w += 1;
                    last_r += 1;
                }
                break;
        }

        if (last_b + last > max) {
            max = last_b + last;
        }
        if (last_r + last > max) {
            max = last_r + last;
        }

        // cout << s[i] << last_b << ':' << last_r << ':' << last_w << ' ' << last << endl;
        if (max > n) {
            max = n;
        }
    }

    fout << max << '\n';

    return 0;
}
