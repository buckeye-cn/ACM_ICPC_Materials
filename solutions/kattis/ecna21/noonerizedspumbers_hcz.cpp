// https://open.kattis.com/problems/noonerizedspumbers

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

    long v1, v2, v3;
    char op, eq;
    cin >> v1 >> op >> v2 >> eq >> v3;

    for (long i = 10; i <= v1; i *= 10) {
        for (long j = 10; j <= v2; j *= 10) {
            long vv1 = v1 % i + v2 / j * i;
            long vv2 = v2 % j + v1 / i * j;
            long vv3 = v3;

            if (op == '+' && vv1 + vv2 == vv3) {
                cout << vv1 << " + " << vv2 << " = " << vv3 << endl;
            } else if (op == '*' && vv1 * vv2 == vv3) {
                cout << vv1 << " * " << vv2 << " = " << vv3 << endl;
            }
        }
    }

    for (long i = 10; i <= v1; i *= 10) {
        for (long j = 10; j <= v3; j *= 10) {
            long vv1 = v1 % i + v3 / j * i;
            long vv2 = v2;
            long vv3 = v3 % j + v1 / i * j;

            if (op == '+' && vv1 + vv2 == vv3) {
                cout << vv1 << " + " << vv2 << " = " << vv3 << endl;
            } else if (op == '*' && vv1 * vv2 == vv3) {
                cout << vv1 << " * " << vv2 << " = " << vv3 << endl;
            }
        }
    }

    for (long i = 10; i <= v2; i *= 10) {
        for (long j = 10; j <= v3; j *= 10) {
            long vv1 = v1;
            long vv2 = v2 % i + v3 / j * i;
            long vv3 = v3 % j + v2 / i * j;

            if (op == '+' && vv1 + vv2 == vv3) {
                cout << vv1 << " + " << vv2 << " = " << vv3 << endl;
            } else if (op == '*' && vv1 * vv2 == vv3) {
                cout << vv1 << " * " << vv2 << " = " << vv3 << endl;
            }
        }
    }

    return 0;
}
