// https://open.kattis.com/problems/cornhusker

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

    int s = 0;

    for (int i = 0; i < 5; ++i) {
        int a, l;
        cin >> a >> l;

        s += a * l;
    }

    int n, kwf;
    cin >> n >> kwf;

    cout << s / 5 * n / kwf << endl;

    return 0;
}
