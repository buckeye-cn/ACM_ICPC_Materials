// https://open.kattis.com/problems/cheeseifyouplease
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

double x[51][100];
double y[51];

void simplex(int n_equ, int n_var) {
    while (true) {
        int best_j = -1;

        for (int j = 0; j < n_var; ++j) {
            if (x[0][j] > 0) {
                best_j = j;
                break;
            }
        }

        if (best_j < 0) {
            break;
        }

        int best_i = -1;
        double best_v = INFINITY;

        for (int i = 1; i < n_equ; ++i) {
            if (x[i][best_j] > 0 && best_v > y[i] / x[i][best_j]) {
                best_i = i;
                best_v = y[i] / x[i][best_j];
            }
        }

        for (int i = 0; i < n_equ; ++i) {
            if (i == best_i) {
                double factor = x[best_i][best_j];

                for (int j = 0; j < n_var; ++j) {
                    x[i][j] /= factor;
                }

                y[i] /= factor;
            } else {
                double factor = x[i][best_j] / x[best_i][best_j];

                for (int j = 0; j < n_var; ++j) {
                    x[i][j] -= x[best_i][j] * factor;

                    if (abs(x[i][j]) < 1e-9) {
                        x[i][j] = 0;
                    }
                }

                y[i] -= y[best_i] * factor;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> y[i];
    }

    for (int i = 0; i < n; ++i) {
        x[i + 1][i] = 1;
    }

    for (int j = n; j < n + m; ++j) {
        for (int i = 1; i <= n; ++i) {
            cin >> x[i][j];
            x[i][j] /= 100;
        }

        cin >> x[0][j];
    }

    simplex(n + 1, n + m);
    printf("%.2f\n", -y[0]);

    return 0;
}
