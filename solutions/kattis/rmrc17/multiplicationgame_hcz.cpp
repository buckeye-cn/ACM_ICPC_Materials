// https://open.kattis.com/problems/multiplicationgame

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool notprime[50000];

void factor(long &value, long &p, long &pn) {
    for (; value != 1; ++p) {
        for (; p < 50000 && notprime[p]; ++p);
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

    notprime[0] = true;
    notprime[1] = true;

    for (int i = 2; i < 25000; ++i) {
        if (notprime[i]) continue;

        for (int j = 2; i * j < 50000; ++j) {
            notprime[i * j] = true;
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
