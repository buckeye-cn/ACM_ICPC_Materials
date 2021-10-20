// https://open.kattis.com/problems/recount

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    unordered_map<string, int> m;

    while (true) {
        string s;
        getline(cin, s);

        if (s == "***") {
            break;
        }

        m[s] += 1;
    }

    int best = 0;
    string best_s = "Runoff!";

    for (pair<string, int> p: m) {
        if (best == p.second) {
            best_s = "Runoff!";
        } else if (best < p.second) {
            best = p.second;
            best_s = p.first;
        }
    }

    cout << best_s << endl;

    return 0;
}
