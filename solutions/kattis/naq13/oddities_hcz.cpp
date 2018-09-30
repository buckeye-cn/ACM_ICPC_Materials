// https://open.kattis.com/problems/oddities

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

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        if (x & 1) {
            cout << x << " is odd" << endl;
        } else {
            cout << x << " is even" << endl;
        }
    }

    return 0;
}
