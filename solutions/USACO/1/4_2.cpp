/*
ID: hu.13381
PROG: milk3
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

bool possible_abc[100][100][100];
bool possible_c[100];
int xa, xb, xc;

void exec(int a, int b, int c) {
    // cout << a << ' ' << b << ' ' << c << endl;
    // if (a > xa || b > xb || c > xc) return;
    if (possible_abc[a][b][c]) return;
    possible_abc[a][b][c] = true;
    if (a == 0) possible_c[c] = true;
    if (b+a > xb) exec(a-xb+b, xb, c); else exec(0, b+a, c);
    if (c+a > xc) exec(a-xc+c, b, xc); else exec(0, b, c+a);
    if (a+b > xa) exec(xa, b-xa+a, c); else exec(a+b, 0, c);
    if (c+b > xc) exec(a, b-xc+c, xc); else exec(a, 0, c+b);
    if (a+c > xa) exec(xa, b, c-xa+a); else exec(a+c, b, 0);
    if (b+c > xb) exec(a, xb, c-xb+b); else exec(a, b+c, 0);
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");

    fin >> xa >> xb >> xc;

    exec(0, 0, xc);

    bool sp = false;
    for (int i = 0; i < 100; ++i) {
        if (possible_c[i]) {
            if (sp) fout << ' ';
            fout << i;
            sp = true;
        }
    }
    fout << endl;

    return 0;
}
