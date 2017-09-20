/*
ID: hu.13381
PROG: zerosum
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

void go(
    ofstream &fout, char *sbegin, char *s,
    int i, int n, bool positive,
    int tot, int last
) {
    if (i > n) {
        if (tot == 0) {
            s[1] = 0;
            fout << sbegin << endl;
        }
    } else {
        s[1] = ' ';
        go(
            fout, sbegin, s + 2,
            i + 1, n, positive,
            tot + (positive ? 1 : -1) * (i + 9 * last), i + 10 * last
        );
        s[1] = '+';
        go(
            fout, sbegin, s + 2,
            i + 1, n, true,
            tot + i, i
        );
        s[1] = '-';
        go(
            fout, sbegin, s + 2,
            i + 1, n, false,
            tot - i, i
        );
    }
}

int main() {
    ofstream fout ("zerosum.out");
    ifstream fin ("zerosum.in");

    int n;
    fin >> n;

    char s[] = "1 2 3 4 5 6 7 8 9";

    go(fout, s, s, 2, n, true, 1, 1);

    return 0;
}
