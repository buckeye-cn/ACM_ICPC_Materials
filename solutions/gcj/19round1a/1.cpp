#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int r, c;
bool used[20][20];
int pre_i[20][20];
int pre_j[20][20];
int fin_i;
int fin_j;

bool dfs(int i, int j, int step) {
    if (!step) {
        fin_i = i;
        fin_j = j;

        return true;
    }

    for (int pos = 0; pos < r * c; ++pos) {
        int k, l;
        if (r < c) {
            k = (pos / c + i) % r;
            l = (pos % c + j) % c;
        } else {
            k = (pos % r + i) % r;
            l = (pos / r + j) % c;
        }

        if (i == k) continue;
        if (j == l) continue;
        if (i + j == k + l) continue;
        if (i - j == k - l) continue;
        if (used[k][l]) continue;

        used[k][l] = true;
        pre_i[k][l] = i;
        pre_j[k][l] = j;

        if (dfs(k, l, step - 1)) {
            return true;
        }

        used[k][l] = false;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        cin >> r >> c;

        memset(used, 0, sizeof(used));
        used[0][0] = true;

        if (dfs(0, 0, r * c - 1)) {
            cout << "POSSIBLE" << endl;

            while (fin_i || fin_j) {
                cout << fin_i + 1 << ' ' << fin_j + 1 << endl;

                int i = pre_i[fin_i][fin_j];
                int j = pre_j[fin_i][fin_j];

                fin_i = i;
                fin_j = j;
            }

            cout << "1 1" << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
