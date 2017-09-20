/*
ID: hu.13381
PROG: runround
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

int main() {
    ofstream fout ("runround.out");
    ifstream fin ("runround.in");

    unsigned n;
    fin >> n;

    static const unsigned exp10[10] = {
        0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
    };

    function<void (unsigned, unsigned, unsigned, unsigned, unsigned)> f =
        [&](unsigned len, unsigned cur, unsigned val, unsigned dmask, unsigned pmask) {
            if (val) {
                if (val + 10 * exp10[cur] <= n) {
                    return;
                }
                if (!cur) {
                    // verify
                    unsigned ppmask = 0;
                    unsigned pos = 1;
                    for (unsigned i = 0; i < len; ++i) {
                        unsigned digit = val / exp10[pos] % 10;
                        pos = ((len * 10 + pos - digit - 1) % len + 1);
                        ppmask |= 1u << pos;
                    }
                    if (ppmask == ((1u << len) - 1) << 1) {
                        fout << val << endl;
                        exit(0);
                    } else {
                        return;
                    }
                }
            } else {
                if (!cur) {
                    return;
                }
                f(len - 1, cur - 1, 0, 0, 0);
            }

            for (unsigned i = 1; i <= 9; ++i) {
                if ((1u << i) & dmask) continue;
                unsigned p = ((len * 10 + cur - i) % len);
                if ((1u << p) & pmask) continue;
                f(len, cur - 1, val + i * exp10[cur], dmask | (1u << i), pmask | (1u << p));
            }
        };

    f(9, 9, 0, 0, 0);

    return 0;
}
