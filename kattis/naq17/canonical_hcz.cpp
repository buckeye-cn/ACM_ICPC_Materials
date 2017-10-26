// https://open.kattis.com/problems/canonical

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n;
int coin[128];
int dp[2000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> coin[i];
    }

    dp[0] = 0;
    for (int i = 1; i < 2000000; ++i) {
        dp[i] = 1 << 30;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = coin[i]; j < 2000000; ++j) {
            int a = dp[j - coin[i]] + 1;

            if (dp[j] > a) {
                dp[j] = a;
            }
        }
    }

    for (int i = 1; i < 2000000; ++i) {
        int v = 0;
        int remain = i;

        for (int j = n - 1; j >= 0; --j) {
            v += remain / coin[j];
            remain -= remain / coin[j] * coin[j];
        }

        if (dp[i] != v) {
            cout << "non-canonical" << endl;

            return 0;
        }
    }

    cout << "canonical" << endl;

    return 0;
}
