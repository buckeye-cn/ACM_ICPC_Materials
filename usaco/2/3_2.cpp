/*
ID: hu.13381
PROG: nocows
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

int cnt[300][300]; // [n][k]

int main() {
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");

    int n, k;
    fin >> n >> k;

    cnt[1][1] = 1;
    for (int ni = 3; ni <= n; ni += 2) {
        for (int ki = 2; ki <= k; ++ki) {
            for (int n1 = 1; n1 < ni; n1 += 2) {
                for (int k1 = 1; k1 < ki - 1; ++k1) {
                    int n2 = ni - 1 - n1;
                    int k2 = ki - 1;
                    cnt[ni][ki] += cnt[n1][k1] * cnt[n2][k2];
                    cnt[ni][ki] = cnt[ni][ki] % 9901;
                }
                int k1 = ki - 1;
                for (int k2 = 1; k2 < ki; ++k2) {
                    int n2 = ni - 1 - n1;
                    cnt[ni][ki] += cnt[n1][k1] * cnt[n2][k2];
                    cnt[ni][ki] = cnt[ni][ki] % 9901;
                }
            }
        }
    }

    fout << cnt[n][k] % 9901 << endl;

    return 0;
}
