#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int grid[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];

            if (i && j) {
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            } else if (i) {
                grid[i][j] += grid[i - 1][j];
            } else if (j) {
                grid[i][j] += grid[i][j - 1];
            }
        }
    }

    cout << grid[n - 1][n - 1] << endl;

    return 0;
}
