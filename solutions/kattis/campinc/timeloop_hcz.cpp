// https://open.kattis.com/problems/timeloop

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

    for (int i = 1; i <= n; ++i) {
        cout << i << " Abracadabra" << endl;
    }

    return 0;
}
