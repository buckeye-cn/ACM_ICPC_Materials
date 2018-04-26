// https://open.kattis.com/problems/simplification

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int x[210000];
int y[210000];

int l_node[210000];
int r_node[210000];
int area[210000];

int cross(int i) {
    int l = l_node[i];
    int r = r_node[i];

    return abs(
        x[l] * y[i] + x[i] * y[r] + x[r] * y[l]
        - x[i] * y[l] - x[r] * y[i] - x[l] * y[r]
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }

    multiset<pair<int, int>> areas;

    for (int i = 1; i <= n - 1; ++i) {
        l_node[i] = i - 1;
        r_node[i] = i + 1;
        area[i] = cross(i);
        areas.insert({area[i], i});
    }

    for (int step = 0; step < n - m; ++step) {
        pair<int, int> p = *areas.begin();

        cout << p.second << endl;

        areas.erase(p);

        int l = l_node[p.second];
        int r = r_node[p.second];

        if (l != 0) {
            areas.erase({area[l], l});
            r_node[l] = r;
            area[l] = cross(l);
            areas.insert({area[l], l});
        }

        if (r != n) {
            areas.erase({area[r], r});
            l_node[r] = l;
            area[r] = cross(r);
            areas.insert({area[r], r});
        }
    }

    return 0;
}
