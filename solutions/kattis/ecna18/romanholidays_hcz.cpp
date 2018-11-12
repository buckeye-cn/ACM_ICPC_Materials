// https://open.kattis.com/problems/romanholidays

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

string roman(int v) {
    int value[] {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string symbol[] {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    string result;

    for (int i = 0; v; ++i) {
        while (v >= value[i]) {
            result += symbol[i];
            v -= value[i];
        }
    }

    return result;
}

int order[2000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    set<pair<string, int>> lo_set;
    set<pair<string, int>> hi_set;

    for (int i = 1; i < 2000; ++i) {
        string s = roman(i);

        if (s < "MMMMMMMMMMMMM") {
            lo_set.insert({s, i});
        } else {
            hi_set.insert({s, i});
        }
    }

    int pos = 1;
    for (pair<string, int> p: lo_set) {
        order[p.second] = pos++;
    }

    pos = -hi_set.size();
    for (pair<string, int> p: hi_set) {
        order[p.second] = pos++;
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;

        cout << v / 1000 * (order[v % 1000 + 1000] - order[v % 1000]) + order[v % 1000] << endl;
    }

    return 0;
}
