/*
ID: hu.13381
PROG: ariprog
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

bool ss[200000];

int main() {
    ofstream fout ("ariprog.out");
    ifstream fin ("ariprog.in");

    int n, m;
    fin >> n >> m;

    for (int p = 0; p <= m; ++p) {
        for (int q = p; q <= m; ++q) {
            ss[p * p + q * q] = true;
        }
    }

    int mx1 = m * m;
    int mx2 = 2 * m * m;
    int ok2 = false;
    for (int step = 1; step <= mx1; ++step) {
        int maxv = step * (n - 1);
        // can skip some values (just like BM algorithm)
        for (int init = 0; init + maxv <= mx2; ++init) {
            int val = init + maxv;
            int ok1 = true;
            for (int i = 0; i < n; val -= step, ++i) {
                if (!ss[val]) {
                    ok1 = false;
                    break;
                }
            }
            if (ok1) {
                fout << init << ' ' << step << endl;
                ok2 = true;
            }
        }
    }

    if (!ok2) {
        fout << "NONE" << endl;
    }

    return 0;
}
