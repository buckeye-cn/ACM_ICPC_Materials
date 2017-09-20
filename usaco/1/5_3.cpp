/*
ID: hu.13381
PROG: sprime
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

unsigned xmap[100 * 1024 * 1024 / 32 / 2];

int main() {
    ofstream fout ("sprime.out");
    ifstream fin ("sprime.in");

    #define get_xmap(i) (xmap[(i) >> 1 >> 5] & (1 << (((i) >> 1) & 31)))
    #define set_xmap(i) xmap[(i) >> 1 >> 5] |= (1 << (((i) >> 1) & 31))
    #define unset_xmap(i) xmap[(i) >> 1 >> 5] &= ~(1 << (((i) >> 1) & 31))

    for (int i = 3; i < 10240; i += 2) {
        if (!get_xmap(i)) {
            for (int j = 3; j * i < 10240 * 10240; j += 2) { // fast enough :)
                set_xmap(i * j);
            }
        }
    }

    int c;
    fin >> c;

    function<void (int, int)> test = [&](int v, int c) {
        if (get_xmap(v)) {
            return;
        }
        if (c == 0) {
            fout << v << endl;
            return;
        }
        test(10 * v + 1, c - 1);
        test(10 * v + 3, c - 1);
        test(10 * v + 7, c - 1);
        test(10 * v + 9, c - 1);
    };

    test(2, c - 1);
    test(3, c - 1);
    test(5, c - 1);
    test(7, c - 1);

    return 0;
}
