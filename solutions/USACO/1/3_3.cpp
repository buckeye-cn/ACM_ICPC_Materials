/*
ID: hu.13381
PROG: crypt1
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
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    bool digits[10] = {false, false, false, false, false, false, false, false, false, false};

    int c;
    fin >> c;
    for (int i = 0; i < c; ++i) {
        int t;
        fin >> t;
        digits[t] = true;
    }

    #define loop(i) for (int i = 1; i < 10; ++i) if (digits[i])

    //    a b c
    // x    d e
    //  -------
    //    f g h
    //  i j k
    //  -------
    //  l m n h

    int tot = 0;

    loop(e) {
        loop(c) {
            int h = c * e % 10;
            int hh = c * e / 10;
            if (digits[h]) loop(b) {
                int g = (b * e + hh) % 10;
                int gg = (b * e + hh) / 10;
                if (digits[g]) loop (a) {
                    int f = (a * e + gg);
                    if (f < 10 && digits[f]) {
                        loop(d) {
                            int k = c * d % 10;
                            if (!digits[k]) continue;
                            int kk = c * d / 10;
                            int j = (b * d + kk) % 10;
                            if (!digits[j]) continue;
                            int jj = (b * d + kk) / 10;
                            int i = (a * d + jj);
                            if (!(i < 10 && digits[i])) continue;
                            int n = (g + k) % 10;
                            if (!digits[n]) continue;
                            int nn = (g + k) / 10;
                            int m = (f + j + nn) % 10;
                            if (!digits[m]) continue;
                            int mm = (f + j + nn) / 10;
                            int l = i + mm;
                            if (!(l < 10 && digits[l])) continue;
                            ++tot;
                            cout << a << b << c << ' ' << d << e << endl;
                            cout << f << g << h << ' ' << i << j << k << endl;
                            cout << l << m << n << h << endl;
                        }
                    }
                }
            }
        }
    }

    fout << tot << endl;

    return 0;
}
