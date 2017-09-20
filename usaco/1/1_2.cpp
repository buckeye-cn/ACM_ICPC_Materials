/*
ID: hu.13381
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    std::string a, b;
    fin >> a >> b;
    int sa = 1;
    int sb = 1;
    for (auto x: a) {sa *= (x - 'A' + 1); sb %= 47;}
    for (auto x: b) {sb *= (x - 'A' + 1); sb %= 47;}
    fout << (sa % 47 == sb % 47 ? "GO":"STAY") << endl;
    return 0;
}
