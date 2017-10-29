/*
ID: hu.13381
PROG: money
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

long long cnt[20000];

int main() {
    ofstream fout ("money.out");
    ifstream fin ("money.in");

    int v, n;
    fin >> v >> n;

    set<int> coins;
    for (int i = 0; i < v; ++i) {
        int c;
        fin >> c;
        coins.insert(c);
    }

    cnt[0] = 1;
    for (int c: coins) {
        for (int i = n; i > 0; --i) {
            for (int i1 = i - c; i1 >= 0; i1 -= c) {
                cnt[i] += cnt[i1];
            }
        }
    }

    fout << cnt[n] << endl;

    return 0;
}
