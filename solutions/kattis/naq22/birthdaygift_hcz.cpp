// https://open.kattis.com/problems/birthdaygift

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define MOD 1000000007l

using namespace std;

long vec[61][9][10];
long mat[60][9][10][9][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    long a, b;
    cin >> a >> b;

    if (a == 1) {
        cout << (b <= 9) << endl;

        return 0;
    }

    for (long bb = b % 25; bb < 100; bb += 25) {
        if (bb / 10 != bb % 10) {
            vec[0][(bb / 10 + bb % 10) % 9][bb / 10] = 1;
        }
    }

    a -= 2;

    for (long i = 0; i < 9; ++i) {
        for (long j = 0; j < 10; ++j) {
            for (long k = 0; k < 10; ++k) {
                if (j != k) {
                    mat[0][i][j][(i + k) % 9][k] = 1;
                }
            }
        }
    }

    for (long d = 1; d < 60; ++d) {
        for (long i = 0; i < 9; ++i) {
            for (long j = 0; j < 10; ++j) {
                for (long k = 0; k < 9; ++k) {
                    for (long s = 0; s < 10; ++s) {
                        for (long t = 0; t < 9; ++t) {
                            for (long r = 0; r < 10; ++r) {
                                mat[d][i][j][t][r] += mat[d - 1][i][j][k][s] * mat[d - 1][k][s][t][r];
                                mat[d][i][j][t][r] %= MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    for (long d = 1; d <= 60; ++d) {
        if (a & (1l << (d - 1))) {
            for (long i = 0; i < 9; ++i) {
                for (long j = 0; j < 10; ++j) {
                    for (long k = 0; k < 9; ++k) {
                        for (long s = 0; s < 10; ++s) {
                            vec[d][k][s] += vec[d - 1][i][j] * mat[d - 1][i][j][k][s];
                            vec[d][k][s] %= MOD;
                        }
                    }
                }
            }
        } else {
            for (long i = 0; i < 9; ++i) {
                for (long j = 0; j < 10; ++j) {
                    vec[d][i][j] = vec[d - 1][i][j];
                }
            }
        }
    }

    long tot = 0;

    for (long i = 1; i <= 9; ++i) {
        tot += vec[60][b % 9][i];
        tot %= MOD;
    }

    cout << tot << endl;

    return 0;
}
