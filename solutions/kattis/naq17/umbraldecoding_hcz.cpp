// https://open.kattis.com/problems/umbraldecoding

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

#define cube(x) (__int128(x) * __int128(x) * __int128(x))

using namespace std;

long size;
int k;
long x[120];
long y[120];
long b[120];
vector<pair<pair<long, long>, pair<long, long>>> rect;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> size >> k;

    for (int i = 0; i < k; ++i) {
        cin >> x[i] >> y[i] >> b[i];
    }

    rect.push_back({{0, 0}, {size, size}});

    long tot = 0;

    while (!rect.empty()) {
        pair<pair<long, long>, pair<long, long>> item = rect.back();
        long left = item.first.first;
        long top = item.first.second;
        long right = item.second.first;
        long bottom = item.second.second;

        // cerr << left << ' ' << top << ' ' << right << ' ' << bottom << endl;

        rect.pop_back();

        bool overlap = false;
        bool cover = false;

        for (int i = 0; i < k; ++i) {
            long test_x = x[i];
            if (test_x < left) test_x = left;
            if (test_x > right) test_x = right;

            long test_y = y[i];
            if (test_y < top) test_y = top;
            if (test_y > bottom) test_y = bottom;

            if (cube(abs(test_x - x[i])) + cube(abs(test_y - y[i])) <= b[i]) {
                if (
                    cube(abs(left - x[i])) + cube(abs(top - y[i])) <= b[i]
                    && cube(abs(right - x[i])) + cube(abs(top - y[i])) <= b[i]
                    && cube(abs(left - x[i])) + cube(abs(bottom - y[i])) <= b[i]
                    && cube(abs(right - x[i])) + cube(abs(bottom - y[i])) <= b[i]
                ) {
                    cover = true;

                    break;
                }

                overlap = true;

                break;
            }
        }

        if (cover) {
            // ignore
        } else if (overlap) {
            if (right - left > bottom - top) {
                long mid_x = (left + right) / 2;

                rect.push_back({{left, top}, {mid_x, bottom}});
                rect.push_back({{mid_x + 1, top}, {right, bottom}});
            } else {
                long mid_y = (top + bottom) / 2;

                rect.push_back({{left, top}, {right, mid_y}});
                rect.push_back({{left, mid_y + 1}, {right, bottom}});
            }
        } else {
            tot += (right - left + 1) * (bottom - top + 1);
        }
    }

    cout << tot << endl;

    return 0;
}
