// https://open.kattis.com/problems/stampcombinations

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int m, n;
    cin >> m >> n;

    for (int i = 1; i <= m; ++i) {
        int vv;
        cin >> vv;

        v[i] = v[i - 1] + vv;
    }

    string s;

    for (int i = 0; i < n; ++i) {
        int q;
        cin >> q;

        q = v[m] - q;

        int p = 0;
        bool ok = false;

        if (q >= 0) {
            for (int j = 0; j <= m; ++j) {
                while (v[j] - v[p] > q) {
                    p += 1;
                }

                if (v[j] - v[p] == q) {
                    ok = true;
                    break;
                }
            }
        }

        if (ok) {
            s += "Yes\n";
        } else {
            s += "No\n";
        }
    }

    cout << s;

    return 0;
}
