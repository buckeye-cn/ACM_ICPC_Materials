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

    int n, t;
    cin >> n >> t;

    double p = double(t > n ? 2 * n + 1 - t : t - 1) / n / n;

    cout << round(1000 * p) << "/1000" << endl;

    return 0;
}
