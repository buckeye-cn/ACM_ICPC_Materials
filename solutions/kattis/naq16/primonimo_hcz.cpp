// https://open.kattis.com/problems/primonimo

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

int inv[100];
int lcm[100][100];
int x[400][401];
int y[400];

int gaussian(int n_equ, int n_var, int mod) {
    int row, col;

    for (row = 0, col = 0; row < n_equ && col < n_var; ++row, ++col) {
        int best_i = row;

        for (int i = row + 1; i < n_equ; ++i) {
            if (abs(x[i][col]) > abs(x[best_i][col])) {
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
                int ta = lcm[x[row][col]][x[i][col]] / x[i][col];
                int tb = lcm[x[row][col]][x[i][col]] / x[row][col];

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

    int n, m, p;
    cin >> n >> m >> p;

    for (int i = 1; i < p; ++i) {
        for (int j = 1; j < p; ++j) {
            if (i * j % p == 1) {
                inv[i] = j;
            }

            lcm[i][j] = i * j / gcd(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> x[i * m + j][n * m];
            x[i * m + j][n * m] = p - x[i * m + j][n * m];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < m; ++l) {
                    if (i == k || j == l) {
                        x[i * m + j][k * m + l] = 1;
                    }
                }
            }
        }
    }

    // for (int i = 0; i < n * m; ++i) {
    //     for (int j = 0; j < n * m + 1; ++j) {
    //         cerr << x[i][j] << ' ';
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;

    if (gaussian(n * m, n * m, p) == -1) {
        cout << -1 << endl;

        return 0;
    }

    // for (int i = 0; i < n * m; ++i) {
    //     for (int j = 0; j < n * m + 1; ++j) {
    //         cerr << x[i][j] << ' ';
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;
    // for (int i = 0; i < n * m; ++i) {
    //     cerr << y[i] << ' ';
    // }
    // cerr << endl;
    // cerr << endl;

    int total = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            total += y[i * m + j];
        }
    }

    cout << total << endl;

    bool first = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < y[i * m + j]; ++k) {
                if (first) {
                    first = false;
                } else {
                    cout << ' ';
                }

                cout << i * m + j + 1;
            }
        }
    }

    cout << endl;

    return 0;
}
