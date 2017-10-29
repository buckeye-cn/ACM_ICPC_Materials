/*
ID: hu.13381
PROG: palsquare
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

bool mirr(string &s) {
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
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

    int n;
    fin >> n;

    for (int i = 1; i <= 300; ++i) {
        int sq = i * i;
        string sqs = base(n, sq);
        if (mirr(sqs)) {
            fout << base(n, i) << ' ' << sqs << endl;
        }
    }

    return 0;
}
