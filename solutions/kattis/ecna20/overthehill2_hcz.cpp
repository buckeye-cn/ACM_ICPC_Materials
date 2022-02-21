// https://open.kattis.com/problems/overthehill2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int gcd(int y, int x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int inv[37];
int g[37][37];
int x[2000][101];
int y[100];

int gaussian(int n_equ, int n_var, int mod) {
    int row, col;

    for (row = 0, col = 0; row < n_equ && col < n_var; ++row, ++col) {
        int best_i = row;

        for (int i = row + 1; i < n_equ; ++i) {
            if (x[i][col] > x[best_i][col]) {
                best_i = i;
            }
        }

        if (!x[best_i][col]) {
            row -= 1;
            continue;
        }

        if (best_i != row) {
            for (int j = col; j < n_var + 1; ++j) {
                swap(x[row][j], x[best_i][j]);
            }
        }

        for (int i = row + 1; i < n_equ; ++i) {
            if (x[i][col]) {
                int ta = x[row][col] * inv[g[x[row][col]][x[i][col]]];
                int tb = x[i][col] * inv[g[x[row][col]][x[i][col]]];

                if (x[i][col] * x[row][col] < 0) {
                    tb = -tb;
                }

                for (int j = col; j < n_var + 1; ++j) {
                    x[i][j] = ((x[i][j] * ta - x[row][j] * tb) % mod + mod) % mod;
                }
            }
        }
    }

    for (int i = row; i < n_equ; ++i) {
        if (x[i][n_var]) {
            return -1;
        }
    }

    for (int i = row - 1; i >= 0; --i) {
        int target = x[i][n_var];
        int first = i;

        while (!x[i][first]) {
            first += 1;
        }

        for (int j = first + 1; j < n_var; ++j) {
            if (x[i][j]) {
                target -= x[i][j] * y[j];
                target = (target % mod + mod) % mod;
            }
        }

        y[first] = target * inv[x[i][first]] % mod;
    }

    return n_var - row;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 1; i < 37; ++i) {
        for (int j = 1; j < 37; ++j) {
            if (i * j % 37 == 1) {
                inv[i] = j;
            }

            g[i][j] = gcd(i, j);
        }
    }

    int n;
    cin >> n;

    cin.get();

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            if (s1[i] >= 'A') {
                x[i / n * n + j][i % n + j * n] = s1[i] - 'A';
            } else if (s1[i] >= '0') {
                x[i / n * n + j][i % n + j * n] = s1[i] - '0' + 26;
            } else {
                x[i / n * n + j][i % n + j * n] = 36;
            }
        }

        if (s2[i] >= 'A') {
            x[i][n * n] = s2[i] - 'A';
        } else if (s2[i] >= '0') {
            x[i][n * n] = s2[i] - '0' + 26;
        } else {
            x[i][n * n] = 36;
        }
    }

    int r = gaussian(s1.size(), n * n, 37);

    if (r == -1) {
        cout << "No solution" << endl;
    } else if (r) {
        cout << "Too many solutions" << endl;
    } else {
        for (int i = 0; i < n * n; ++i) {
            cout << y[i];

            if (i % n == n - 1) {
                cout << endl;
            } else {
                cout << ' ';
            }
        }
    }

    return 0;
}
