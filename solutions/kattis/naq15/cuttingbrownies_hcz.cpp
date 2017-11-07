// https://open.kattis.com/problems/cuttingbrownies

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

int n;
bool win[501][501];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    for (int i = 1; i <= 500; ++i) {
        for (int j = 1; j <= 500; ++j) {
            win[i][j] = false;

            for (int k = 1; k < j; ++k) {
                win[i][j] = win[i][j] || (!win[k][i] && !win[j - k][i]);
            }
        }
    }

    cin >> n;

    for (int i = 0; i < n; ++i) {
        int b, d;
        string s;
        cin >> b >> d >> s;

        cout << s << ' ';
        if (s[0] == 'H') {
            cout << (win[b][d] ? "can win" : "cannot win") << endl;
        } else {
            cout << (win[d][b] ? "can win" : "cannot win") << endl;
        }
    }

    return 0;
}
