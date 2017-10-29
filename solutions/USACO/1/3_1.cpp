/*
ID: hu.13381
PROG: milk
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
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

    int tot, c;
    fin >> tot >> c;

    map<int, int> prices {};
    for (int i = 0; i < c; ++i) {
        int p, u;
        fin >> p >> u;

        if (prices.find(p) != prices.end()) {
            prices[p] += u;
        } else {
            prices[p] = u;
        }
        cout << p << ' ' << u << endl;
    }

    int sum = 0;
    for (auto i: prices) {
        cout << i.first << ' ' << i.second << ' ' << tot << endl;
        if (i.second >= tot) {
            sum += i.first * tot;
            tot = 0;
            break;
        } else {
            sum += i.first * i.second;
            tot -= i.second;
        }
    }

    fout << sum << endl;

    return 0;
}
