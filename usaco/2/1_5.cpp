/*
ID: hu.13381
PROG: hamming
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

unsigned ham(unsigned i, unsigned j) {
    unsigned k = i ^ j;
    unsigned result = 0;
    while (k & -k) {
        k ^= (k & -k);
        ++result;
    }
    return result;
}

int main() {
    ofstream fout ("hamming.out");
    ifstream fin ("hamming.in");

    unsigned n, b, d;
    fin >> n >> b >> d;
    vector<unsigned> result;

    for (unsigned i = 0; i < (1u << b); ++i) {
        bool ok = true;
        for (unsigned j: result) {
            if (ham(i, j) < d) {
                ok = false;
                break;
            }
        }
        if (ok) {
            result.push_back(i);
            fout << i;
            if (result.size() == n) {
                fout << endl;
                return 0;
            } else if (result.size() % 10 == 0) {
                fout << endl;
            } else {
                fout << ' ';
            }
        }
    }

    return 0;
}
