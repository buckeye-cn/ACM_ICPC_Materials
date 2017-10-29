/*
ID: hu.13381
PROG: dualpal
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

string base(int n, int val) {
    string result = "";
    while (val) {
        result = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[val % n] + result;
        val = val / n;
    }
    return result;
}

bool mirr(const string &s) {
    int size = s.size();
    int xx = s.size() >> 1;
    for (int i = 0; i < xx; ++i) {
        if (s[i] != s[size - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

    int n, s;
    fin >> n >> s;

    int c = 0;
    for (int i = s + 1; c != n; ++i) {
        int jc = 0;
        for (int j = 2; j <= 10; ++j) {
            if (mirr(base(j, i))) {
                ++jc;
            }
        }
        if (jc >= 2) {
            fout << i << endl;
            ++c;
        }
    }

    return 0;
}
