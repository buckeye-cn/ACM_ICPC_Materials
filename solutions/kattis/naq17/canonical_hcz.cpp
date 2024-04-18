// https://open.kattis.com/problems/canonical

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int dp[2000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;

    int coin[n];

    for (int i = 0; i < n; ++i) {
        cin >> coin[i];
    }

    for (int i = 1; i < 2000000; ++i) {
        dp[i] = 1 << 30;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = coin[i]; j < 2000000; ++j) {
            dp[j] = min(dp[j], dp[j - coin[i]] + 1);
        }
    }

    int i = 0;

    for (int j = 1; j < 2000000; ++j) {
        i += i + 1 < n && coin[i + 1] <= j;

        if (dp[j] <= dp[j - coin[i]]) {
            cout << "non-canonical" << endl;

            return 0;
        }
    }

    cout << "canonical" << endl;

    return 0;
}
