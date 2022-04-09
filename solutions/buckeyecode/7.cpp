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

    int v = 0;

    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;

        v = (v * 10 + (c - '0')) % 11;
    }

    cout << v << endl;
}
