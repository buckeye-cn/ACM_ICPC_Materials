// https://open.kattis.com/problems/cold

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

    int total = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;

        total += t < 0;
    }

    cout << total << endl;

    return 0;
}
