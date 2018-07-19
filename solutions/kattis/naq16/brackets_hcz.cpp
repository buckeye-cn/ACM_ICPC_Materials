// https://open.kattis.com/problems/brackets

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int delta[6000][6000];
int minv[6000][6000];
int maxv[6000][6000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    string s;

    cin >> s;

    if (s.size() & 1) {
        cout << "impossible" << endl;

        return 0;
    }

    for (int i = 0; i < s.size(); ++i) {
        for (int j = i + 1; j <= s.size(); ++j) {
            delta[i][j] = delta[i][j - 1] + (s[j - 1] == '(' ? 1 : -1);
            if (delta[i][j] < minv[i][j - 1]) {
                minv[i][j] = delta[i][j];
            } else {
                minv[i][j] = minv[i][j - 1];
            }
            if (delta[i][j] > maxv[i][j - 1]) {
                maxv[i][j] = delta[i][j];
            } else {
                maxv[i][j] = maxv[i][j - 1];
            }
        }
    }

    // for (int i = 0; i < s.size(); ++i) {
    //     for (int j = i; j <= s.size(); ++j) {
    //         cerr << i << ':' << j << ' ' << delta[i][j] << ' ' << minv[i][j] << ' ' << maxv[i][j] << endl;
    //     }
    // }

    for (int i = 0; i < s.size(); ++i) {
        for (int j = i; j <= s.size(); ++j) {
            if (
                minv[0][i] >= 0
                && delta[0][i] - maxv[i][j] >= 0
                && delta[0][i] - delta[i][j] + minv[j][s.size()] >= 0
                && delta[0][i] - delta[i][j] + delta[j][s.size()] == 0
            ) {
                cout << "possible" << endl;

                return 0;
            }
        }
    }

    cout << "impossible" << endl;

    return 0;
}
