// https://open.kattis.com/problems/skocimis

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

    int a, b, c;
    cin >> a >> b >> c;

    cout << max(c - b, b - a) - 1 << endl;

    return 0;
}
