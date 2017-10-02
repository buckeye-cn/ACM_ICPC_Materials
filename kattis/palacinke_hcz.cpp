// https://open.kattis.com/problems/palacinke
// not AC yet

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, m, t;
int item[25][25];
// int dp_mat[32][25][16][2][25][16][2];
// int dp[32][25][16][2];
int dp[2][25][16][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // TODO: naive implementation

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        string s;
        cin >> a >> b >> s;

        int bitmap = 0;
        for (char c: s) {
            switch (c) {
                case 'B':
                    bitmap |= 1;
                    break;
                case 'J':
                    bitmap |= 2;
                    break;
                case 'M':
                    bitmap |= 4;
                    break;
                case 'P':
                    bitmap |= 8;
                    break;
            }
        }

        item[a - 1][b - 1] = bitmap;
    }

    cin >> t;

    dp[0][0][0][0] = 1;

    int tot = 0;

    for (int i = 0; i < t; ++i) {
        memset(dp[(i & 1) ^ 1], 0, sizeof(dp[(i & 1) ^ 1]));
        for (int j = 0; j < 25; ++j) {
            for (int status = 0; status < 16; ++status) {
                dp[(i & 1) ^ 1][j][status][false] += dp[i & 1][j][status][true];
                dp[(i & 1) ^ 1][j][status][false] %= 5557;

                for (int k = 0; k < 25; ++k) {
                    if (!item[j][k]) continue;

                    dp[(i & 1) ^ 1][k][status | item[j][k]][true] += dp[i & 1][j][status][false];
                    dp[(i & 1) ^ 1][k][status | item[j][k]][true] %= 5557;
                    dp[(i & 1) ^ 1][k][status][false] += dp[i & 1][j][status][false];
                    dp[(i & 1) ^ 1][k][status][false] %= 5557;
                }
            }
        }

        tot += dp[(i & 1) ^ 1][0][15][false];
        tot %= 5557;
    }

    cout << tot << endl;

    return 0;
}
