// https://open.kattis.com/problems/gearsandaxles

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int v[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    multiset<pair<int, int>> gset;

    for (int i = 0; i < n; ++i) {
        int s, c;
        cin >> s >> c;

        gset.insert({s, c});
    }

    gset.insert({1000000, 0});

    int vcount = 0;
    int prev = 0;
    double result = 0;

    for (pair<int, int> p: gset) {
        if (prev != p.first) {
            for (int i = 0; i < vcount / 2; ++i) {
                result -= log(v[i]);
                result += log(v[vcount - 1 - i]);
            }

            vcount = 0;
            prev = p.first;
        }

        v[vcount++] = p.second;
    }

    cout << result << endl;

    return 0;
}
