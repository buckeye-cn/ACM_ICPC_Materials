/*
ID: hu.13381
PROG: fracdec
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

char str[110000];
int pos[110000];

int main() {
    ofstream fout ("fracdec.out");
    ifstream fin ("fracdec.in");

    int write_n = 0;
    auto write = [&](char c) {
        if (write_n && write_n % 76 == 0) fout << endl;
        fout << c;
        write_n += 1;
    };

    int n, d;
    fin >> n >> d;

    fout << n / d << '.';
    write_n += 2 + to_string(n / d).size();
    if (n % d == 0) {
        write('0');
    } else {
        int r = n % d;

        int i;
        for (i = 1; !pos[r]; ++i) {
            pos[r] = i;
            r *= 10;
            str[i] = '0' + r / d;
            r = r % d;
        }

        for (int j = 1; j < pos[r]; ++j) {
            write(str[j]);
        }
        if (str[pos[r]] != '0' || pos[r] + 1 < i) {
            fout << '(';
            for (int j = pos[r]; j < i; ++j) {
                write(str[j]);
            }
            write(')');
        }
    }
    fout << endl;

    return 0;
}
