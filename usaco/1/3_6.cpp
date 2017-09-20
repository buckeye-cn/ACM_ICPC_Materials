/*
ID: hu.13381
PROG: skidesign
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
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");

    int c;
    vector<int> h;
    fin >> c;
    for (int i = 0; i < c; ++i) {
        int x;
        fin >> x;
        h.push_back(x);
    }
    sort(h.begin(), h.end());

    if (c == 0 || h[h.size() - 1] - h[0] <= 17) {
        fout << 0 << endl;
    } else {
        int minp = 0x7fffffff;
        for (int i = h[0]; i <= h[h.size() - 1] - 17; ++i) {
            int p = 0;
            for (int hh: h) {
                if (i > hh) {
                    p += (i - hh) * (i - hh);
                }
                if (i + 17 < hh) {
                    p += (hh - i - 17) * (hh - i - 17);
                }
            }
            if (p < minp) {
                minp = p;
            }
        }
        fout << minp << endl;
    }

    return 0;
}
