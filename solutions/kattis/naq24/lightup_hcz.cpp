// https://open.kattis.com/problems/lightup

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

char grid[32][32];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }

    int valid = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '.' || grid[i][j] == '?') {
                int count = 0;

                for (int ii = i - 1; ii >= 1; --ii) {
                    if (grid[ii][j] == '.') continue;

                    count += grid[ii][j] == '?';
                    break;
                }

                for (int ii = i + 1; ii <= n; ++ii) {
                    if (grid[ii][j] == '.') continue;

                    count += grid[ii][j] == '?';
                    break;
                }

                for (int jj = j - 1; jj >= 1; --jj) {
                    if (grid[i][jj] == '.') continue;

                    count += grid[i][jj] == '?';
                    break;
                }

                for (int jj = j + 1; jj <= n; ++jj) {
                    if (grid[i][jj] == '.') continue;

                    count += grid[i][jj] == '?';
                    break;
                }

                if (grid[i][j] == '.') {
                    valid &= count >= 1;
                } else {
                    valid &= count == 0;
                }
            }

            if (grid[i][j] >= '0' && grid[i][j] <= '4') {
                valid &= grid[i][j] - (grid[i - 1][j] == '?') - (grid[i + 1][j] == '?') - (grid[i][j - 1] == '?') - (grid[i][j + 1] == '?') == '0';
            }
        }
    }

    cout << valid << endl;

    return 0;
}
