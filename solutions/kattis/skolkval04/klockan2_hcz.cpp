// https://open.kattis.com/problems/klockan2

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

    printf("%02d:%02d", n * 131 / 300 % 12, n * 11 / 5 % 60);

    return 0;
}
