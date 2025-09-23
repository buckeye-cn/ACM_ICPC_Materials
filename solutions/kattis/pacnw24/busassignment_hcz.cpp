// https://open.kattis.com/problems/busassignment

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

    int curr = 0;
    int best = 0;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        curr += b - a;
        best = max(best, curr);
    }

    cout << best << endl;

    return 0;
}
