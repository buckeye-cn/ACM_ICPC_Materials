// https://open.kattis.com/problems/narrowartgallery

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n, k;
int dp01[2][240];
int dp10[2][240];
int dp11[2][240];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> k;

    for (int i = 0; i <= k; ++i) {
        dp01[0][i] = -(1 << 30);
        dp10[0][i] = -(1 << 30);
        dp11[0][i] = -(1 << 30);
    }
    dp11[0][0] = 0;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        for (int j = 0; j <= k; ++j) {
            dp01[(i & 1) ^ 1][j + 1] = max(dp01[i & 1][j], dp11[i & 1][j]) + b;
            dp10[(i & 1) ^ 1][j + 1] = max(dp10[i & 1][j], dp11[i & 1][j]) + a;
            dp11[(i & 1) ^ 1][j] = max(max(dp01[i & 1][j], dp10[i & 1][j]), dp11[i & 1][j]) + a + b;
        }
    }

    cout << max(max(dp01[n & 1][k], dp10[n & 1][k]), dp11[n & 1][k]) << endl;

    return 0;
}
