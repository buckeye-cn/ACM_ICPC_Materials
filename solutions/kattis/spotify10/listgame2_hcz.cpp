// https://open.kattis.com/problems/listgame2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int gen(__int128 counts, __int128 reduces, int tot_c, int tot_r, int result) {
    // algorithm from judge's answer

    // cerr << tot_c << ' ' << tot_r << ' ' << result << ':';
    // for (int i = 0; i < tot_c; ++i) cerr << '\t' << long((counts >> (8 * i)) & 255);
    // for (int i = 0; i < tot_r; ++i) cerr << '\t' << long((reduces >> (8 * i)) & 255);
    // cerr << endl;

    while (true) {
        int sum = 0;
        for (int i = 0; i < 16; ++i) {
            sum += (counts >> (8 * i)) & 255;
        }

        if (result >= sum / tot_r) {
            return result;
        }

        for (int i = 0; true; ++i) {
            reduces += __int128(1) << (8 * i);

            if (((reduces >> (8 * i)) & 255) < tot_c) {
                break;
            }

            if (i == tot_r - 1) {
                reduces = 0;
                tot_r += 1;
                break;
            }

            reduces >>= (8 * i + 8);
            reduces <<= 8;
            reduces |= (reduces >> 8) & 255;
            reduces += 1;

            for (int j = 0; j < i; ++j) {
                reduces <<= 8;
                reduces |= (reduces >> 8) & 255;
            }
        }

        __int128 new_counts = counts;

        for (int i = 0; i < tot_r; ++i) {
            int pp = (reduces >> (8 * i)) & 255;

            if ((new_counts >> (8 * pp)) & 255) {
                new_counts -= __int128(1) << (8 * pp);
            } else {
                new_counts = -1;
                break;
            }
        }

        if (new_counts != -1) {
            result = 1 + gen(new_counts, reduces, tot_c, tot_r, max(result - 1, 0));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long x;
    cin >> x;

    int tot = 0;
    int tot_c = 0;
    __int128 counts = 0;

    for (long i = 2; i * i <= x; i += 1 + (i > 2)) {
        int count = 0;

        while (x % i == 0) {
            x /= i;
            count += 1;
        }

        if (count) {
            tot += 1;

            if (count > 1) {
                counts <<= 8;
                counts |= __int128(count - 1);
                tot_c += 1;
            }
        }
    }

    if (x != 1) {
        tot += 1;
    }

    if (tot_c) {
        tot += gen(counts, tot_c, tot_c, 1, 0);
    }

    cout << tot << endl;

    return 0;
}
