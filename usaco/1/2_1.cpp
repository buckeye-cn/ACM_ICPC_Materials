/*
ID: hu.13381
PROG: milk2
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
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    int n;
    vector<pair<int, int>> times;
    set<int> keys;

    fin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        fin >> a >> b;
        times.push_back({a, b});
        keys.insert(a);
        keys.insert(b);
    }

    vector<pair<int, int>> counts;
    map<int, int> imap;
    for (int i: keys) {
        imap[i] = counts.size();
        counts.push_back({i, 0});
    }

    for (auto i: times) {
        int iend = imap[i.second];
        for (int j = imap[i.first]; j < iend; j++) {
            ++counts[j].second;
        }
    }

    int len0 = 0;
    int lenx = 0;
    int cur0 = 0;
    int curx = 0;
    int lastt = 0;
    bool last0 = false;
    bool lastx = false;
    for (auto i: counts) {
        if (last0) {
            cur0 += i.first - lastt;
            if (cur0 > len0) len0 = cur0;
        } else {
            cur0 = 0;
        }
        if (lastx) {
            curx += i.first - lastt;
            if (curx > lenx) lenx = curx;
        } else {
            curx = 0;
        }

        lastt = i.first;
        last0 = false;
        lastx = false;
        if (i.second == 0) {
            last0 = true;
        } else {
            lastx = true;
        }
    }

    fout << lenx << ' ' << len0 << endl;

    return 0;
}
