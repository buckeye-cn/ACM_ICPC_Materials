// https://open.kattis.com/problems/convexhull

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int tot_lo;
int tot_hi;
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

        map<int, int> bound_lo;
        map<int, int> bound_hi;

        for (int j = 0; j < n; ++j) {
            int x, y;
            cin >> x >> y;

            if (bound_lo.find(x) == bound_lo.end()) {
                bound_lo.insert({x, y});
                bound_hi.insert({x, y});
            } else {
                bound_lo[x] = min(bound_lo[x], y);
                bound_hi[x] = max(bound_hi[x], y);
            }
        }

        tot_lo = 0;
        stack_lo[tot_lo++] = {bound_lo.begin()->first, bound_lo.begin()->second + 1};

        for (const pair<int, int> &i: bound_lo) {
            while (tot_lo >= 2) {
                pair<int, int> &p1 = stack_lo[tot_lo - 2];
                pair<int, int> &p2 = stack_lo[tot_lo - 1];

                if (
                    (i.second - p1.second) * (p2.first - p1.first)
                    <= (p2.second - p1.second) * (i.first - p1.first)
                ) {
                    tot_lo -= 1;
                } else {
                    break;
                }
            }

            stack_lo[tot_lo++] = i;
        }

        tot_hi = 0;
        stack_hi[tot_hi++] = {bound_hi.begin()->first, bound_hi.begin()->second - 1};

        for (const pair<int, int> &i: bound_hi) {
            while (tot_hi >= 2) {
                pair<int, int> &p1 = stack_hi[tot_hi - 2];
                pair<int, int> &p2 = stack_hi[tot_hi - 1];

                if (
                    (i.second - p1.second) * (p2.first - p1.first)
                    >= (p2.second - p1.second) * (i.first - p1.first)
                ) {
                    tot_hi -= 1;
                } else {
                    break;
                }
            }

            stack_hi[tot_hi++] = i;
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

        for (int i = tot_hi - 1; i >= 1; --i) {
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

        for (int i = tot_hi - 1; i >= 1; --i) {
            if (stack_hi[i] != last && stack_hi[i] != first) {
                last = stack_hi[i];
                cout << last.first << ' ' << last.second << endl;
            }
        }
    }
}
