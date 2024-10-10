// https://open.kattis.com/problems/statues

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int nums[2501];
int grid[50][50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    int tot = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];

            if (grid[i][j] > 0) {
                nums[tot++] = grid[i][j];
            }
        }
    }

    nums[tot] = 2147483647;
    sort(nums, nums + tot);

    int best = n * m;

    for (int mode = 0; mode < 4; ++mode) {
        int curr = 0;
        int pos = mode < 2 ? 0 : tot;

        for (int t = 0; t < n + m - 1; ++t) {
            int tail = pos;

            for (int i = max(0, t - m + 1); i < min(n, t + 1); ++i) {
                int j = mode % 2 == 0 ? t - i : m - 1 - t + i;

                if (grid[i][j] > 0) {
                    tail += mode < 2 ? 1 : -1;
                }
            }

            for (int i = max(0, t - m + 1); i < min(n, t + 1); ++i) {
                int j = mode % 2 == 0 ? t - i : m - 1 - t + i;

                if (grid[i][j] > 0 && (grid[i][j] >= nums[pos]) == (grid[i][j] >= nums[tail])) {
                    curr += 1;
                }
            }

            pos = tail;
            // cerr << mode << '\t' << curr << endl;
        }

        best = min(best, curr);
    }

    cout << best << endl;

    return 0;
}
