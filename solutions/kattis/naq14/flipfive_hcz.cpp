// https://open.kattis.com/problems/flipfive

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

    int masks[512];

    masks[0x001] = 0x001 ^ 0x002         ^ 0x008;
    masks[0x002] = 0x001 ^ 0x002 ^ 0x004 ^ 0x010;
    masks[0x004] =         0x002 ^ 0x004 ^ 0x020;

    masks[0x008] = 0x008 ^ 0x010         ^ 0x001 ^ 0x040;
    masks[0x010] = 0x008 ^ 0x010 ^ 0x020 ^ 0x002 ^ 0x080;
    masks[0x020] =         0x010 ^ 0x020 ^ 0x004 ^ 0x100;

    masks[0x040] = 0x040 ^ 0x080         ^ 0x008;
    masks[0x080] = 0x040 ^ 0x080 ^ 0x100 ^ 0x010;
    masks[0x100] =         0x080 ^ 0x100 ^ 0x020;


    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int mask = 0;

        for (int j = 0; j < 9; ++j) {
            char c;
            cin >> c;

            if (c == '*') {
                mask |= 1 << j;
            }
        }

        int best = 512;

        for (int j = 0; j < 512; ++j) {
            int mask2 = 0;
            int count = 0;

            for (int k = j; k; k &= ~(k & -k)) {
                mask2 ^= masks[k & -k];
                ++count;
            }

            if (mask2 == mask) {
                if (best > count) {
                    best = count;
                }
            }
        }

        cout << best << endl;
    }
}
