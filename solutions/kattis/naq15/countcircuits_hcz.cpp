// https://open.kattis.com/problems/countcircuits

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

const int BASE = 402;
const int CAP = BASE * BASE;

using namespace std;

int ii[CAP];
long value[CAP];
long count[2][CAP];
int tot;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    value[0] = CAP / 2;
    count[0][0] = 1;
    tot = 1;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        long *count_last = count[i & 1];
        long *count_now = count[(i & 1) ^ 1];
        int delta = x * BASE + y;
        int old_tot = tot;

        for (int j = 0; j < old_tot; ++j) {
            count_now[j] += count_last[j];
            if (ii[value[j] + delta]) {
                count_now[ii[value[j] + delta]] += count_last[j];
            } else if (value[j] + delta == CAP / 2) {
                count_now[0] += count_last[j];
            } else {
                value[tot] = value[j] + delta;
                count_now[tot] += count_last[j];
                ii[value[tot]] = tot;
                tot += 1;
            }
            count_last[j] = 0;
        }
    }

    cout << (count[n & 1][0] - 1) << endl;

    return 0;
}
