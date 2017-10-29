/*
ID: hu.13381
PROG: pprime
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
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");

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

    int min, max;
    fin >> min >> max;
    set<int> result;

    auto test = [&](int v) {
        if (v >= min && v <= max && !get_xmap(v)) {
            result.insert(v);
        }
    };

    std::function<void (int, int, int)> x = [&](int head, int tail, int mul) {
        for (int i = 0; i < 10; ++i) {
            test(head * 10 + i * mul + tail);
            test(head * 100 + i * mul * 11 + tail);
            if (mul < 10000) {
                x(head * 100 + i * mul * 10, tail + i * mul, mul * 10);
            }
        }
    };

    test(5);
    test(7);
    test(11);
    x(10, 1, 10);
    x(30, 3, 10);
    x(70, 7, 10);
    x(90, 9, 10);

    for (int i: result) {
        fout << i << endl;
    }

    return 0;
}
