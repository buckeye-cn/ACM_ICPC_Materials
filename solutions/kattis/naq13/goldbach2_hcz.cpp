// https://open.kattis.com/problems/goldbach2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool notprime[40000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    notprime[0] = true;
    notprime[1] = true;

    for (int i = 2; i < 20000; ++i) {
        if (notprime[i]) continue;

        for (int j = 2; i * j < 40000; ++j) {
            notprime[i * j] = true;
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        int tot = 0;

        for (int j = 2; j * 2 <= x; ++j) {
            if (!notprime[j] && !notprime[x - j]) {
                tot += 1;
            }
        }

        cout << x << " has " << tot << " representation(s)" << endl;

        for (int j = 2; j * 2 <= x; ++j) {
            if (!notprime[j] && !notprime[x - j]) {
                cout << j << '+' << x - j << endl;
            }
        }

        cout << endl;
    }

    return 0;
}
