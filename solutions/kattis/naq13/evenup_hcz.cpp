// https://open.kattis.com/problems/evenup

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

    int m = 0;
    int tot = 0;
    int cur = 0;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;

        if ((v & 1) == m) {
            cur += 1;
        } else {
            if (cur & 1) {
                tot += 1;
                cur = 1;
            } else if (tot) {
                tot -= 1;
                cur = 2;
            } else {
                cur = 1;
            }

            m = v & 1;
        }
    }

    if (cur & 1) {
        tot += 1;
    }

    cout << tot << endl;

    return 0;
}
