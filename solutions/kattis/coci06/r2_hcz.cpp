// https://open.kattis.com/problems/r2

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

    int r, s;
    cin >> r >> s;

    cout << s * 2 - r << endl;

    return 0;
}
