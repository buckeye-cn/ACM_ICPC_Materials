#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

long delta = 10000000000l;
long total = 1000000000000l;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t, w;
    cin >> t >> w;

    for (int n_case = 1; n_case <= t; ++n_case) {
        set<long> values {total + 1};

        while (true) {
            long p;
            cin >> p;

            if (p < 0) {
                break;
            }

            values.insert(p);

            long last = 1;
            int count = 0;
            long target = 1;

            for (long v: values) {
                if (v - last == 2 * delta) {
                    target = last;
                    count += 1;
                } else {
                    if (v - last >= 3 * delta) {
                        target = last + 2 * delta;
                        count = 0;
                        break;
                    }

                    if (v - last >= delta) {
                        target = last + (v - last - delta) / 2;
                        count = 0;
                        break;
                    }
                }

                last = v + delta;
            }

            if (count & 1) {
                target += 1;
            }

            cout << target << endl;
            values.insert(target);
        }
    }

    return 0;
}
