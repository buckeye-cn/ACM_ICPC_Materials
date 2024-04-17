// https://open.kattis.com/problems/kolkrabbaleikarnir

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

    int n, m;
    cin >> n >> m;

    double s = 0;

    for (int i = 0; i < m; ++i) {
        s += (m - i) * exp(lgamma(n + 1) - lgamma(i + 1) - lgamma(n - i + 1) - n * log(2));
    }

    cout << s << endl;

    return 0;
}
