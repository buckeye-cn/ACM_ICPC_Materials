// https://open.kattis.com/problems/happytrails

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const double PI = acos(-1);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    double h = 0;

    for (int i = 0; i < n; ++i) {
        int a, l;
        cin >> a >> l;

        h += l * sin(a * PI / 180);
    }

    printf("%.2f\n", h);

    return 0;
}
