// https://open.kattis.com/problems/timeessence

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    string name[12];
    int conv[12];

    for (int i = 0; i < n; ++i) {
        if (i) cin >> conv[i];
        cin >> name[i];
    }

    int tot;
    cin >> tot;

    long base[12];
    base[n - 1] = 1;

    for (int i = n - 1; i >= 1; --i) {
        if (base[i] <= 4000000000) {
            base[i - 1] = base[i] * conv[i];
        } else {
            base[i - 1] = base[i];
        }
    }

    int v0 = tot / base[0] + (2 * (tot % base[0]) >= base[0]);
    int v1 = tot / base[1] + (2 * (tot % base[1]) >= base[1]);

    cout << v0 << ' ' << name[0] << endl;
    cout << v1 / conv[1] << ' ' << name[0] << ' '
         << v1 - v1 / conv[1] * conv[1] << ' ' << name[1] << endl;

    return 0;
}
