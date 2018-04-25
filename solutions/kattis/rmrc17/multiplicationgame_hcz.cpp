// https://open.kattis.com/problems/multiplicationgame

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool prime[65536];

void factor(long &value, long &p, long &pn) {
    for (; value != 1; ++p) {
        for (; p < 65536 && !prime[p]; ++p);
        if (p * p > value) {
            p = value;
        }

        if (value % p == 0) {
            break;
        }
    }

    for (; value % p == 0 && value != 1; ++pn) {
        value /= p;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 2; i < 65536; ++i) {
        prime[i] = true;
    }

    for (int i = 2; i < 65536; ++i) {
        if (!prime[i]) continue;

        for (int j = i * 2; j < 65536; j += i) {
            prime[j] = false;
        }
    }

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        long value;
        string player;
        cin >> value >> player;

        long p1 = 2;
        long pn1 = 0;
        factor(value, p1, pn1);

        long p2 = p1 + 1;
        long pn2 = 0;
        factor(value, p2, pn2);

        if (value != 1) {
            cout << "tie" << endl;
        } else if (pn1 && pn2 && (pn1 > pn2 + 1 || pn2 > pn1 + 1)) {
            cout << "tie" << endl;
        } else {
            if (((player == "Alice") ^ (pn1 + pn2)) & 1) {
                cout << "Bob" << endl;
            } else {
                cout << "Alice" << endl;
            }
        }
    }

    return 0;
}
