// https://open.kattis.com/problems/rings2

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int ring[120][120];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;

            if (c == 'T') {
                ring[i][j] = 100;
            }
        }
    }

    for (int iter = 0; iter < 50; ++iter) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                ring[i][j] = min(ring[i][j], ring[i][j - 1] + 1);
                ring[i][j] = min(ring[i][j], ring[i][j + 1] + 1);
                ring[i][j] = min(ring[i][j], ring[i - 1][j] + 1);
                ring[i][j] = min(ring[i][j], ring[i + 1][j] + 1);
            }
        }
    }

    int maxring = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            maxring = max(maxring, ring[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (maxring >= 10) {
                if (ring[i][j] >= 10) {
                    cout << '.' << ring[i][j];
                } else if (ring[i][j] >= 1) {
                    cout << ".." << ring[i][j];
                } else {
                    cout << "...";
                }
            } else {
                if (ring[i][j] >= 1) {
                    cout << '.' << ring[i][j];
                } else {
                    cout << "..";
                }
            }
        }
        cout << endl;
    }

    return 0;
}
