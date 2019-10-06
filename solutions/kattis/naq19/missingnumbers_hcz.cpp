// https://open.kattis.com/problems/missingnumbers

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

    int last = 0;
    bool ok = true;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        for (++last; last < x; ++last) {
            ok = false;
            cout << last << endl;
        }
    }

    if (ok) {
        cout << "good job" << endl;
    }

    return 0;
}
