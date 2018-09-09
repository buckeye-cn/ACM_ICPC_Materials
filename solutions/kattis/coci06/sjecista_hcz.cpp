// https://open.kattis.com/problems/sjecista

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

    cout << n * (n - 1) * (n - 2) * (n - 3) / 24 << endl;

    return 0;
}
