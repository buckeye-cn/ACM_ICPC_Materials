#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int grid[100][100];
int best[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            best[i][j] = -1 << 30;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i) {
                if (grid[i - 1][j] < grid[i][j]) {
                    best[i][j] = max(best[i][j], best[i - 1][j] + grid[i][j]);
                }
            } else {
                best[i][j] = max(best[i][j], grid[i][j]);
            }
        }

        for (int j = 1; j < n; ++j) {
            if (grid[i][j - 1] < grid[i][j]) {
                best[i][j] = max(best[i][j], best[i][j - 1] + grid[i][j]);
            }
        }

        for (int j = n - 2; j >= 0; --j) {
            if (grid[i][j + 1] < grid[i][j]) {
                best[i][j] = max(best[i][j], best[i][j + 1] + grid[i][j]);
            }
        }
    }

    int result = -1 << 30;

    for (int i = 0; i < n; ++i) {
        result = max(result, best[m - 1][i]);
    }

    if (result < -1 << 29) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
