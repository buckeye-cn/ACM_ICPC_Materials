// https://open.kattis.com/problems/grille

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    bool hole[n][n];
    int tot_hole = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;

            hole[i][j] = c == '.';
            tot_hole += hole[i][j];
        }
    }

    string s;
    cin >> s;

    if (tot_hole * 4 != n * n) {
        cout << "invalid grille" << endl;

        return 0;
    }

    int si = 0;

    string result;
    result.resize(n * n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (hole[i][j]) {
                result[i * n + j] = s[si++];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (hole[n - 1 - j][i]) {
                result[i * n + j] = s[si++];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (hole[n - 1 - i][n - 1 - j]) {
                result[i * n + j] = s[si++];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (hole[j][n - 1 - i]) {
                result[i * n + j] = s[si++];
            }
        }
    }

    for (char c: result) {
        if (!c) {
            cout << "invalid grille" << endl;

            return 0;
        }
    }

    cout << result << endl;

    return 0;
}
