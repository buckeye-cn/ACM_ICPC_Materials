// https://open.kattis.com/problems/randomproblem

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int v[1000];

int count[10][10][10];
int first[10][10][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int p;
    cin >> p;

    for (int i = 0; i < p; ++i) {
        cin >> v[i];
    }

    int best_first = 1000;
    int best_n;
    int best_m;

    for (int n = 1; n < p; ++n) {
        for (int m = 1; n + m < p; ++m) {
            memset(count, 0, sizeof(count));
            memset(first, 0, sizeof(first));

            for (int i = 0; i + n + m < p; ++i) {
                int a = v[i];
                int b = v[i + n];
                int c = v[i + n + m];

                if (count[a][b][c] > 0) {
                    count[a][b][c] += 1;
                } else {
                    count[a][b][c] = 1;
                    first[a][b][c] = i;
                }
            }

            for (int a = 0; a <= 9; ++a) {
                for (int b = 0; b <= 9; ++b) {
                    for (int c = 0; c <= 9; ++c) {
                        if (count[a][b][c] * 40 >= p + 40 && best_first > first[a][b][c]) {
                            bool ok = true;

                            for (int aa = 0; aa < 9; ++aa) {
                                ok &= a == aa || !count[aa][b][c];
                            }

                            for (int bb = 0; bb < 9; ++bb) {
                                ok &= b == bb || !count[a][bb][c];
                            }

                            for (int cc = 0; cc < 9; ++cc) {
                                ok &= c == cc || !count[a][b][cc];
                            }

                            if (ok) {
                                best_first = first[a][b][c];
                                best_n = n;
                                best_m = m;
                            }
                        }
                    }
                }
            }
        }
    }

    if (best_first < p) {
        int a = v[best_first];
        int b = v[best_first + best_n];
        int c = v[best_first + best_n + best_m];

        cout << "triple correlation "
            << a << '(' << best_n << ')'
            << b << '(' << best_m << ')'
            << c << " found" << endl;
    } else {
        cout << "random sequence" << endl;
    }

    return 0;
}
