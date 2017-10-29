/*
ID: hu.13381
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    std::vector<std::string> names;
    std::map<std::string, int> give;
    int c;
    fin >> c;
    for (int i = 0; i < c; ++i) {
        std::string name;
        fin >> name;
        give[name] = 0;
        names.push_back(name);
    }

    while (!fin.eof()) {
        std::string giver;
        fin >> giver;
        int x, count;
        fin >> x >> count;
        if (!count) continue;
        x = x / count;
        give[giver] -= x * count;
        for (int i = 0; i < count; ++i) {
            std::string to;
            fin >> to;
            give[to] += x;
        }
    }

    for (auto x: names) {
        fout << x << ' ' << give[x] << endl;
    }

    return 0;
}
