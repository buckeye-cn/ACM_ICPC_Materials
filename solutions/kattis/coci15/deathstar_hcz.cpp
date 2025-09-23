// https://open.kattis.com/problems/deathstar

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int v = 0;

        for (int j = 0; j < n; ++j) {
            int m;
            cin >> m;

            v |= m;
        }

        cout << v << endl;
    }

    return 0;
}
