// https://open.kattis.com/problems/convexhull

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int lo[20001];
int hi[20001];
pair<int, int> stack_lo[12000];
pair<int, int> stack_hi[12000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    while (true) {
        int n;
        cin >> n;

        if (!n) {
            return 0;
        }

        for (int i = -10000; i <= 10000; ++i) {
            lo[i + 10000] = 10001;
            hi[i + 10000] = -10001;
        }

        int min_x = 10001;
        int max_x = -10001;

        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;

            min_x = min(min_x, x);
            max_x = max(max_x, x);
            lo[x + 10000] = min(lo[x + 10000], y);
            hi[x + 10000] = max(hi[x + 10000], y);
        }

        int tot_lo = 0;
        stack_lo[tot_lo++] = {min_x, 10001};

        for (int i = min_x; i <= max_x; ++i) {
            if (lo[i + 10000] == 10001) continue;

            while (tot_lo >= 2) {
                pair<int, int> &p1 = stack_lo[tot_lo - 2];
                pair<int, int> &p2 = stack_lo[tot_lo - 1];

                if (
                    (lo[i + 10000] - p1.second) * (p2.first - p1.first)
                    <= (p2.second - p1.second) * (i - p1.first)
                ) {
                    tot_lo -= 1;
                } else {
                    break;
                }
            }

            stack_lo[tot_lo++] = {i, lo[i + 10000]};
        }

        int tot_hi = 0;
        stack_hi[tot_hi++] = {max_x, -10001};

        for (int i = max_x; i >= min_x; --i) {
            if (hi[i + 10000] == -10001) continue;

            while (tot_hi >= 2) {
                pair<int, int> &p1 = stack_hi[tot_hi - 2];
                pair<int, int> &p2 = stack_hi[tot_hi - 1];

                if (
                    (hi[i + 10000] - p1.second) * (p2.first - p1.first)
                    <= (p2.second - p1.second) * (i - p1.first)
                ) {
                    tot_hi -= 1;
                } else {
                    break;
                }
            }

            stack_hi[tot_hi++] = {i, hi[i + 10000]};
        }

        int count = 0;

        pair<int, int> first = stack_lo[1];
        pair<int, int> last = {-10001, -10001};

        for (int i = 1; i < tot_lo; ++i) {
            if (stack_lo[i] != last) {
                last = stack_lo[i];
                count += 1;
            }
        }

        for (int i = 1; i < tot_hi; ++i) {
            if (stack_hi[i] != last && stack_hi[i] != first) {
                last = stack_hi[i];
                count += 1;
            }
        }

        cout << count << endl;

        last = {-10001, -10001};

        for (int i = 1; i < tot_lo; ++i) {
            if (stack_lo[i] != last) {
                last = stack_lo[i];
                cout << last.first << ' ' << last.second << endl;
            }
        }

        for (int i = 1; i < tot_hi; ++i) {
            if (stack_hi[i] != last && stack_hi[i] != first) {
                last = stack_hi[i];
                cout << last.first << ' ' << last.second << endl;
            }
        }
    }
}
