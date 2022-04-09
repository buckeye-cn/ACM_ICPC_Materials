#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int x[100][100];
int s[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t;
    cin >> t;

    for (int n_case = 1; n_case <= t; ++n_case) {
        cout << "Case #" << n_case << ": ";

        int e, w;
        cin >> e >> w;

        for (int i = 0; i < e; ++i) {
            s[i][i] = 0;

            for (int j = 0; j < w; ++j) {
                cin >> x[i][j];
                s[i][i] += x[i][j];
            }
        }

        for (int i = 1; i < e; ++i) {
            for (int j = 0; j + i < e; ++j) {
                s[j][j + i] = 1e9;

                for (int k = 0; k < i; ++k) {
                    s[j][j + i] = min(s[j][j + i], s[j][j + k] + s[j + k + 1][j + i]);
                }

                for (int k = 0; k < w; ++k) {
                    x[j][k] = min(x[j][k], x[j + 1][k]);
                    s[j][j + i] -= x[j][k];
                }
            }
        }

        cout << s[0][e - 1] * 2 << endl;
    }

    return 0;
}
