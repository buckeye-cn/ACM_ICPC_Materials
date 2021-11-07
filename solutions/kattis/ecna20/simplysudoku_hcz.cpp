// https://open.kattis.com/problems/simplysudoku

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int grid[9][9];

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int v;
            cin >> v;

            if (v) {
                grid[i][j] = 1 << (v - 1);
            } else {
                grid[i][j] = 511;
            }
        }
    }

    for (int iter = 0; iter < 81; ++iter) {
        for (int i = 0; i < 9; ++i) {
            int used = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i][j];

                if ((target & -target) == target) {
                    used |= target;
                }
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i][j];

                if ((target & -target) != target) {
                    target &= ~used;
                }
            }
        }

        for (int i = 0; i < 9; ++i) {
            int used = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[j][i];

                if ((target & -target) == target) {
                    used |= target;
                }
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[j][i];

                if ((target & -target) != target) {
                    target &= ~used;
                }
            }
        }

        for (int i = 0; i < 9; ++i) {
            int used = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3];

                if ((target & -target) == target) {
                    used |= target;
                }
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3];

                if ((target & -target) != target) {
                    target &= ~used;
                }
            }
        }

        for (int i = 0; i < 9; ++i) {
            int seen2 = 0;
            int seen1 = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i][j];

                seen2 |= seen1 & target;
                seen1 |= target;
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i][j];

                if (target & seen1 & ~seen2) {
                    target &= seen1 & ~seen2;
                }
            }
        }

        for (int i = 0; i < 9; ++i) {
            int seen2 = 0;
            int seen1 = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[j][i];

                seen2 |= seen1 & target;
                seen1 |= target;
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[j][i];

                if (target & seen1 & ~seen2) {
                    target &= seen1 & ~seen2;
                }
            }
        }

        for (int i = 0; i < 9; ++i) {
            int seen2 = 0;
            int seen1 = 0;

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3];

                seen2 |= seen1 & target;
                seen1 |= target;
            }

            for (int j = 0; j < 9; ++j) {
                int &target = grid[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3];

                if (target & seen1 & ~seen2) {
                    target &= seen1 & ~seen2;
                }
            }
        }
    }

    bool easy = true;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            easy &= (grid[i][j] & -grid[i][j]) == grid[i][j];
        }
    }

    if (easy) {
        cout << "Easy" << endl;
    } else {
        cout << "Not easy" << endl;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j) cout << ' ';

            if ((grid[i][j] & -grid[i][j]) == grid[i][j]) {
                for (int k = 1; k <= 9; ++k) {
                    if (grid[i][j] == 1 << (k - 1)) {
                        cout << k;
                    }
                }
            } else {
                cout << '.';
            }
        }

        cout << endl;
    }

    return 0;
}
