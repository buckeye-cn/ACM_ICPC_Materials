// https://open.kattis.com/problems/3dprinter

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

    int result = 1;

    for (int i = 1; i < n; i <<= 1) {
        result += 1;
    }

    cout << min(n, result) << endl;

    return 0;
}
