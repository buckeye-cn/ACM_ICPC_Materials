// https://open.kattis.com/problems/different

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

    long a, b;
    while (cin >> a >> b) {
        cout << abs(a - b) << endl;
    }

    return 0;
}
