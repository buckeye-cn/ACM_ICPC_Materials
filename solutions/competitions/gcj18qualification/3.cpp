#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

bool grid[1001][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        memset(grid, 0, sizeof(grid));

        int a;
        cin >> a;

        int min_x = 500;
        int max_x = 500 + ceil(sqrt(a)) - 1;
        int min_y = 500;
        int max_y = 500 + ceil(a / ceil(sqrt(a))) - 1;

        while (true) {
            int best_blank = 0;
            int best_i = 500;
            int best_j = 500;

            for (int i = min_x + 1; i <= max_x - 1 && best_blank < 9; ++i) {
                for (int j = min_y + 1; j <= max_y - 1 && best_blank < 9; ++j) {
                    int blank = 0;

                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            blank += !grid[i + k][j + l];
                        }
                    }

                    if (blank > best_blank) {
                        best_blank = blank;
                        best_i = i;
                        best_j = j;
                    }
                }
            }

            if (best_blank) {
                cout << best_i << ' ' << best_j << endl;
            } else {
                cout << min_x << ' ' << ((min_y + max_y) / 2) << endl;
            }

            int x, y;
            cin >> x >> y;

            if (x <= 0 && y <= 0) {
                break;
            }

            grid[x][y] = true;
        }
    }

    return 0;
}
