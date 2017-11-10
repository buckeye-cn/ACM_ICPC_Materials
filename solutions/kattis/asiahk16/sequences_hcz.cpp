// https://open.kattis.com/problems/sequences

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

#define MOD 1000000007l

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long n_num = 1;
    long n_1 = 0;
    long n_pair = 0;

    while (true) {
        char c = cin.get();

        switch (c) {
            case '1':
                n_1 = (n_1 + n_num) % MOD;
                break;
            case '0':
                n_pair = (n_pair + n_1) % MOD;
                break;
            case '?':
                n_pair = (2 * n_pair + n_1) % MOD;
                n_1 = (2 * n_1 + n_num) % MOD;
                n_num = (2 * n_num) % MOD;
                break;
            default:
                cout << n_pair << endl;
                return 0;
        }
    }
}
