// https://open.kattis.com/problems/choosingnumbers

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int gcd(int y, int x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;

    while (cin >> n) {
        set<pair<int, int>> all;
        bool removed[n];

        for (int i = 0; i < n; ++i) {
            int v;
            cin >> v;

            all.insert({v, i});
            removed[i] = false;
        }

        for (auto i = all.rbegin(); i != all.rend(); ++i) {
            if (removed[i->second]) continue;

            for (auto j = all.begin(); j != all.end(); ++j) {
                if (*i != *j && gcd(i->first, j->first) > 1) {
                    removed[i->second] = true;
                    removed[j->second] = true;
                    break;
                }
            }

            if (!removed[i->second]) {
                cout << i->first << endl;
                break;
            }
        }
    }

    return 0;
}
