/*
ID: hu.13381
PROG: frac1
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

bool simp(int a, int b) {
    if (a == 1 || b == 1) {
        return true;
    }
    if (a > b) {
        return simp(a - b, b);
    } else if (a < b) {
        return simp(a, b - a);
    } else {
        return false;
    }
}

int main() {
    ofstream fout ("frac1.out");
    ifstream fin ("frac1.in");

    int n;
    fin >> n;

    fout << "0/1" << endl;

    vector<pair<int, int>> data;

    for (int j = 2; j <= n; ++j) {
        for (int i = 1; i < j; ++i) {
            if (simp(i, j)) {
                data.push_back({i, j});
            }
        }
    }

    sort(
        data.begin(), data.end(),
        [](pair<int, int> m, pair<int, int> n) {
            return m.first * n.second < m.second * n.first;
        }
    );

    for (auto i: data) {
        fout << i.first << '/' << i.second << endl;
    }

    fout << "1/1" << endl;

    return 0;
}
