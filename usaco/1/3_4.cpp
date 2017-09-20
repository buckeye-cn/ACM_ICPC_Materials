/*
ID: hu.13381
PROG: combo
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
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");

    int n, a, b, c, d, e, f;
    fin >> n;
    fin >> a >> b >> c;
    fin >> d >> e >> f;

    a += n;
    b += n;
    c += n;
    d += n;
    e += n;
    f += n;

    set<int> xset;

    for (int x = -2; x <= 2; ++x)
    for (int y = -2; y <= 2; ++y)
    for (int z = -2; z <= 2; ++z) {
        xset.insert(
            ((a + x) % n) + 256 * ((b + y) % n) + 65536 * ((c + z) % n)
        );
        xset.insert(
            ((d + x) % n) + 256 * ((e + y) % n) + 65536 * ((f + z) % n)
        );
    }

    fout << xset.size() << endl;

    return 0;
}
