// https://open.kattis.com/problems/smallestcalculatedvalue

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int best;

void test(int ab, int c) {
    if (ab + c >= 0) best = min(best, ab + c);
    if (ab - c >= 0 && ab >= c) best = min(best, ab - c);
    if (ab * c >= 0) best = min(best, ab * c);
    if (ab / c >= 0 && ab % c == 0) best = min(best, ab / c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int a, b, c;
    cin >> a >> b >> c;

    best = a + b + c;

    test(a + b, c);
    test(a - b, c);
    test(a * b, c);
    if (a % b == 0) test(a / b, c);

    cout << best << endl;

    return 0;
}
