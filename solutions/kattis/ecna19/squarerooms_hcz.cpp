// https://open.kattis.com/problems/squarerooms

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m;
string grid[100];
int sum_i[100][100][101];
int sum_j[100][100][101];
int s_lo[100][100];
int s_hi[100][100];

int height[100];
int s_real[100][100];

bool solve(int i, int j) {
    if (j == m) {
        j = 0;
        i += 1;
    }

    if (i == n) {
        return true;
    }

    if (grid[i][j] == '#') {
        height[j] = i + 1;

        if (solve(i, j + 1)) {
            return true;
        }

        height[j] = i;

        return false;
    }

    if (height[j] != i) {
        return solve(i, j + 1);
    }

    for (int k = 1; k < s_lo[i][j]; ++k) {
        if (height[j + k] != i) {
            return false;
        }
    }

    for (int k = s_lo[i][j]; k < s_hi[i][j]; ++k) {
        if (height[j + k] != i) {
            return false;
        }

        for (int l = 0; l <= k; ++l) {
            height[j + l] = i + k + 1;
        }

        // cerr << i << '\t' << j << '\t' << k + 1 << endl;

        if (solve(i, j + 1)) {
            s_real[i][j] = k;

            return true;
        }

        for (int l = 0; l <= k; ++l) {
            height[j + l] = i;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; i + k < n; ++k) {
                sum_i[i][j][k + 1] = sum_i[i][j][k] + grid[i + k][j];
            }

            for (int k = 0; j + k < m; ++k) {
                sum_j[i][j][k + 1] = sum_j[i][j][k] + grid[i][j + k];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int total = 0;

            for (int k = 0; i + k < n && j + k < m; ++k) {
                total += sum_i[i][j + k][k] + sum_j[i + k][j][k];
                total += grid[i + k][j + k];

                if (total == '.' * (k + 1) * (k + 1)) {
                    s_lo[i][j] = k + 1;
                } else if (total == '.' * (k + 1) * (k + 1) - '.' + '$') {
                    s_hi[i][j] = k + 1;
                } else {
                    break;
                }
            }

            // cerr << s_lo[i][j] + 1 << ':' << s_hi[i][j] << '\t';
        }

        // cerr << endl;
    }

    if (solve(0, 0)) {
        int step = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '$' || grid[i][j] == '.') {
                    for (int k = 0; k <= s_real[i][j]; ++k) {
                        for (int l = 0; l <= s_real[i][j]; ++l) {
                            if (step < 26) {
                                grid[i + k][j + l] = 'A' + step;
                            } else {
                                grid[i + k][j + l] = 'a' + step - 26;
                            }
                        }
                    }

                    step += 1;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            cout << grid[i] << endl;
        }
    } else {
        cout << "elgnatcer" << endl;
    }

    return 0;
}
