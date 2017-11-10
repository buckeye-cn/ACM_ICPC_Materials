// https://open.kattis.com/problems/towers

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
int a[200][200];
long double exps[200][200];
int inf[200];
long double first[200];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 200; ++j) {
            cin >> a[i][j];

            if (cin.get() != '^') {
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        exps[i][199] = 1;

        for (int j = 198; j >= 0; --j) {
            if (a[i][j] > 1) {
                exps[i][j] = pow(a[i][j], exps[i][j + 1]);
            } else {
                exps[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 200; ++j) {
            if (exps[i][j] == 1.0 / 0.0) {
                inf[i] += 1;
            } else {
                first[i] = exps[i][j];

                break;
            }
        }

        if (inf[i] >= 2) {
            first[i] = log2(log(a[i][inf[i] - 2])) + log2(a[i][inf[i] - 1]) * first[i];
        } else if (inf[i] >= 1) {
            first[i] = log2(a[i][inf[i] - 1]) * first[i];
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     cout << inf[i] << ' ' << first[i] << endl;
    // }

    cout << "Case 1:" << endl;

    for (int i = 0; i < n; ++i) {
        int x = 0;

        for (int j = 1; j < n; ++j) {
            // compare x, j

            if (inf[j] < inf[x]) {
                x = j;
            } else if (inf[j] == inf[x]) {
                if (first[j] - first[x] < (first[x] + first[j]) * -0.00000000000001l) {
                    x = j;
                } else if (first[j] - first[x] < (first[x] + first[j]) * 0.00000000000001l) {
                    // comparison
                    for (int k = inf[x] - 2; k >= 0; --k) {
                        if (a[j][k] < a[x][k]) {
                            x = j;

                            break;
                        } else if (a[j][k] > a[x][k]) {
                            break;
                        }
                    }
                }
            }
        }

        cout << a[x][0];
        for (int j = 1; j < 200; ++j) {
            if (!a[x][j]) {
                break;
            }

            cout << '^' << a[x][j];
        }
        cout << endl;

        inf[x] = 9999;
    }

    return 0;
}
