// https://ecna16.kattis.com/problems/ecna16.thathanoi

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int tot;
long now;
int pos[100];

int pos_table[2][6] = {{0, 1, 1, 2, 2, 0}, {0, 2, 2, 1, 1, 0}};

int main() {
    ios_base::sync_with_stdio(false);
    cout.precision(10);

    for (int i = 0; i < 3; ++i) {
        int count;
        cin >> count;

        tot += count;

        int last = 100;
        for (int j = 0; j < count; ++j) {
            int curr;
            cin >> curr;

            if (curr >= last) {
                cout << "No" << endl;

                return 0;
            }
            last = curr;

            pos[curr - 1] = i;
        }
    }

    for (int i = tot - 1; i >= 0; --i) {
        now <<= 1;

        if (pos[i] == pos_table[(tot - i) & 1][now % 6]) {
            // nothing
        } else if (pos[i] == pos_table[(tot - i) & 1][now % 6 + 1]) {
            now |= 1;
        } else {
            cout << "No" << endl;

            return 0;
        }
    }

    cout << ((1l << tot) - now - 1l) << endl;

    return 0;
}
