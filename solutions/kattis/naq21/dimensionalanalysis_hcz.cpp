// https://open.kattis.com/problems/dimensionalanalysis

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int gcd(int y, int x) {
    while (x) {
        y %= x;
        swap(y, x);
    }

    return y;
}

int inv[1163];
int x[200][101];
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
                int g = gcd(x[row][col], x[i][col]);
                int ta = x[row][col] * inv[g];
                int tb = x[i][col] * inv[g];

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

    for (int i = 1; i < 1163; ++i) {
        for (int j = 1; j < 1163; ++j) {
            if (i * j % 1163 == 1) {
                inv[i] = j;
            }
        }
    }

    int n;
    cin >> n;

    unordered_map<string, int> m;

    int i = 0;
    int lr = 1;
    int op = 1;
    string s;
    while (cin >> s) {
        if (s == "*") {
            op = 1;
        } else if (s == "/") {
            op = -1;
        } else if (s == "=") {
            lr = -1;
            op = 1;
        } else {
            if (!op) {
                i += 1;
                lr = 1;
                op = 1;
            }

            if (s != "1") {
                int j = m.insert({s, m.size()}).first->second;

                x[i][j] = (x[i][j] + lr * op + 1163) % 1163;
            }

            op = 0;
        }
    }

    while (true) {
        bool ok = true;

        for (int i = 0; i < m.size(); ++i) {
            if (y[i] == 0) {
                x[n][i] = 1;
                x[n][m.size()] = rand() % 1163;
                n += 1;
                ok = false;

                break;
            }
        }

        if (ok) {
            cout << "valid" << endl;

            return 0;
        }

        int r = gaussian(n, m.size(), 1163);

        if (r == -1) {
            cout << "invalid" << endl;

            return 0;
        }
    }
}
