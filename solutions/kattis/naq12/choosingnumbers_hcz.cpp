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
        pair<int, int> v[n];
        bool removed[n];

        for (int i = 0; i < n; ++i) {
            cin >> v[i].first;
            v[i].second = i;
            removed[i] = false;
        }

        sort(v, v + n);

        for (int i = n - 1; i >= 0; --i) {
            if (removed[v[i].second]) continue;

            for (int j = 0; j < n; ++j) {
                if (i != j && gcd(v[i].first, v[j].first) > 1) {
                    removed[v[i].second] = true;
                    removed[v[j].second] = true;
                    break;
                }
            }

            if (!removed[v[i].second]) {
                cout << v[i].first << endl;
                break;
            }
        }
    }

    return 0;
}
