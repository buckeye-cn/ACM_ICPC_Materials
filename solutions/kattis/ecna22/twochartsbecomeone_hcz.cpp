// https://open.kattis.com/problems/twochartsbecomeone

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int p[2][1000001];
int stk[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n = 0;

    for (int i = 0; i < 2; ++i) {
        while (true) {
            char c = cin.get();

            if (c >= '0' && c <= '9') {
                stk[n] *= 10;
                stk[n] += c - '0';
            } else if (c == '(') {
                n += 1;
            } else if (c == ')') {
                p[i][stk[n]] = stk[n - 1];
                stk[n] = 0;
                n -= 1;
            } else if (c == '\n') {
                p[i][stk[n]] = -1;
                stk[n] = 0;
                break;
            }
        }
    }

    for (int i = 0; i < 1000000; ++i) {
        if (p[0][i] != p[1][i]) {
            cout << "No" << endl;

            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
