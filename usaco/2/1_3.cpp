/*
ID: hu.13381
PROG: sort3
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

int diff[4][4];

int min(int a, int b) {
    return a > b ? b : a;
}

int main() {
    ofstream fout ("sort3.out");
    ifstream fin ("sort3.in");

    int n;
    fin >> n;
    vector<int> a, b;
    for (int i = 0; i < n; ++i) {
        int x;
        fin >> x;
        a.push_back(x);
        b.push_back(x);
    }

    sort(b.begin(), b.end());

    for (int i = 0; i < a.size(); ++i) {
        diff[a[i]][b[i]] += 1;
    }

    int tot = 0;

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            if (i != j) {
                int d = min(diff[i][j], diff[j][i]);
                tot += d;
                diff[i][j] -= d;
                diff[j][i] -= d;
            }
        }
    }

    tot += 2 * diff[1][2] + 2 * diff[2][1];

    fout << tot << endl;

    return 0;
}
